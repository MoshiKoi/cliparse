#pragma once
#ifndef USAGEBASE_HPP
#define USAGEBASE_HPP

#include <algorithm>
#include <cstring>
#include <functional>
#include <iterator>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "argument.hpp"
#include "option.hpp"

namespace cli {

namespace details {

template <class... Ts> struct overloaded : Ts... {
	using Ts::operator()...;
};

template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

template <class T>
inline std::tuple<>
something(T arg) {
	return {};
}

template <class T>
inline std::tuple<Option<T>>
something(Option<T> arg) {
	return std::make_tuple(arg);
}

} // namespace details

class UsageBase {
  public:
	virtual ~UsageBase() {}

	virtual std::function<int(void)> parse_execution(int argc, char const *const *argv) const = 0;
};

template <class Fn, class... Args>
    requires std::is_invocable_r_v<int, Fn, typename Args::ret_type...>
class Usage : public UsageBase {
	Fn _fn;
	std::tuple<Args...> _args;
	int _num_pos_args;
	std::vector<std::string> _option_names;
	std::vector<std::string> _flag_names;

  public:
	Usage(Fn fn, Args... args) : _fn{fn}, _args{args...}, _flag_names{}, _option_names{}, _num_pos_args{0} {
		// clang-format off
		(std::invoke(
			details::overloaded {
				[&]<class T>(Option<T> const &opt) { _option_names.emplace_back(opt.get_name()); },
				[&](Option<bool> const &opt) { _flag_names.emplace_back(opt.get_name()); },
				[&]<class T>(Argument<T> const &) { ++_num_pos_args; }
			}, args),...);
		// clang-format on
	}

	std::function<int(void)> parse_execution(int argc, char const *const *argv) const override {
		std::vector<char const *> positional_arguments{};
		std::unordered_map<std::string, char const *> option_arguments{};
		std::unordered_set<std::string> flag_arguments{};

		int index = 1;

		while (index < argc) {
			if (std::strncmp("--", argv[index], 2) == 0) {
				auto const option = std::find(std::begin(_option_names), std::end(_option_names), argv[index]);

				if (option != std::end(_option_names) && index + 1 < argc) {
					option_arguments.emplace(std::make_pair(*option, argv[index + 1]));
					index += 2;
					continue;
				}

				auto const flag = std::find(std::begin(_flag_names), std::end(_flag_names), argv[index]);

				if (flag != std::end(_flag_names)) {
					flag_arguments.emplace(*flag);
					++index;
					continue;
				}

				return nullptr;
			} else {
				positional_arguments.push_back(argv[index]);
				++index;
			}
		}

		if (positional_arguments.size() != _num_pos_args) {
			return nullptr;
		}

		auto positional_argument_iter = std::begin(positional_arguments);

		// clang-format off
		auto const actual_vals = std::apply(
		    [&](auto &&...argument) {
				auto results = std::tuple{std::invoke(details::overloaded {
					[&]<class T>(Argument<T> const &arg) {
						auto const res = arg.parse(*positional_argument_iter);
						++positional_argument_iter;
						return res;
					},
					[&]<class T>(Option<T> const &opt) {
						auto const res = option_arguments.find(opt.get_name());
						if (res == std::end(option_arguments)) {
							return opt.get_default_value();
						} else {
							return opt.parse(res->second);
						}
					}
				}, argument)...};

			    return results;
		    }, _args);
		// clang-format on

		return [=]() { return std::apply(_fn, actual_vals); };
	}
};

} // namespace cli

#endif