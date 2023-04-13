#include "cliparse.hpp"

int
main(int argc, char const **argv) {
	cli::Command program{"program", "description"};

	cli::Command subcommand{"subcommand", "description"};

	subcommand.add_usage([](void) { return 0; });

	program.add_subcommand(std::move(subcommand));

	return program.run(argc, argv);
}