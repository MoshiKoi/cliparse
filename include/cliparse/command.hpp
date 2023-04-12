#pragma once
#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

#include "usage.hpp"

namespace cli {

class Command {
	std::string _name, _description;
	std::vector<std::unique_ptr<UsageBase>> _usages;
	std::map<std::string, Command> _subcommands;

  public:
	Command(std::string const &name, std::string const &description)
	    : _name{name}, _description{description}, _subcommands{} {}

	template <class Fn, class... Args>
	    requires std::is_invocable_r_v<int, Fn, typename Args::ret_type...>
	void add_usage(Fn fn, Args... args) {
		_usages.emplace_back(std::make_unique<Usage<Fn, Args...>>(fn, args...));
	}

	int run(int argc, char const *const *argv) {
		for (auto &&usage : _usages) {
			auto execute = usage->parse_execution(argc, argv);

			if (execute != nullptr) {
				return execute();
			}
		}
		return 1;
	}
};

} // namespace cli

#endif