#include "cliparse.hpp"

int
main(int argc, char const **argv) {
	cli::Command program{"one", "description"};

	cli::Argument<char const *> arg{"arg", "an argument"};

	program.add_usage([](char const *) { return 0; }, arg);

	return program.run(argc, argv);
}