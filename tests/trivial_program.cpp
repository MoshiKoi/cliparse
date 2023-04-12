#include "cliparse.hpp"

int
main(int argc, char const **argv) {
	cli::Command program{"basic_test", "basic description"};

	program.add_usage([]() { return 0; });

	return program.run(argc, argv);
}