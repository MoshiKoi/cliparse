#include <cstring>
#include <iostream>

#include "cliparse.hpp"

int
run(float a, float b, char const *op) {
	if (std::strcmp(op, "add") == 0) {
		std::cout << a << " + " << b << " = " << a + b << std::endl;
	} else if (std::strcmp(op, "sub") == 0) {
		std::cout << a << " - " << b << " = " << a - b << std::endl;
	} else if (std::strcmp(op, "mul") == 0) {
		std::cout << a << " * " << b << " = " << a * b << std::endl;
	} else if (std::strcmp(op, "div") == 0) {
		std::cout << a << " / " << b << " = " << a / b << std::endl;
	} else {
		std::cout << "Not a valid operation!" << std::endl;
		return 1;
	}
	return 0;
}

int
main(int argc, char const **argv) {
	cli::Command program{"calc", "Calculate the sum, difference, product, or division of two numbers"};

	cli::Argument<float> arg1{"arg1", "First number"};
	cli::Argument<float> arg2{"arg2", "Second number"};
	cli::Option<char const *> operation{"--op", "operation", "add"};

	program.add_usage(run, arg1, arg2, operation);

	return program.run(argc, argv);
}