#include "cliparse.hpp"

int
main(int argc, char const **argv) {
	cli::Command program{"foo", "description"};

	cli::Option<char const *> opt{"--opt", "an option", "default"};

	program.add_usage([](char const *) { return 0; }, opt);

    return program.run(argc, argv);
}