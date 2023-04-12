#include <iostream>

#include "cliparse.hpp"

int
main(int argc, char const **argv) {
	cli::Command program{"add", "Add two numbers together"};

	cli::Argument<int> arg1{"arg1", "First number"};
	cli::Argument<int> arg2{"arg2", "Second number"};

	program.add_usage(
	    [](int a, int b) {
		    std::cout << a << " + " << b << " = " << a + b << std::endl;
		    return 0;
	    },
	    arg1, arg2);

	return program.run(argc, argv);
}