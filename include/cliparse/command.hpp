#pragma once
#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#include "usage.hpp"

namespace cli {

class Command {
	std::string _name, _description;
	std::vector<std::unique_ptr<UsageBase>> _usages;
	std::vector<Command> _subcommands;

  public:
	Command(std::string const &name, std::string const &description)
		: _name{name}, _description{description}, _usages{}, _subcommands{} {}

	template <class Fn, class... Args>
		requires std::is_invocable_r_v<int, Fn, typename Args::ret_type...>
	void add_usage(Fn fn, Args... args) {
		_usages.emplace_back(std::make_unique<Usage<Fn, Args...>>(fn, args...));
	}

	int run(int argc, char const *const *argv) const {
		if (argc > 1) {
			for (auto &&subcommand : _subcommands) {
				if (subcommand._name == argv[1]) {
					return subcommand.run(argc - 1, argv + 1);
				}
			}
		}

		for (auto &&usage : _usages) {
			auto execute = usage->parse_execution(argc, argv);

			if (execute != nullptr) {
				return execute();
			}
		}
		return 1;
	}

	void add_subcommand(Command &&other) { _subcommands.emplace_back(std::move(other)); }
};

} // namespace cli

#endif