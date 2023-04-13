#include <cstring>
#include <iostream>

#include "cliparse.hpp"
#include "cliparse/command.hpp"

int
run_add(float a, float b, char const *op) {
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

	cli::Command add_command{"add", "Calculate the sum of two numbers"};
	cli::Command sub_command{"sub", "Calculate the difference of two numbers"};
	cli::Command mul_command{"mul", "Calculate the product of two numbers"};
	cli::Command div_command{"div", "Calculate the division of two numbers"};

	add_command.add_usage(
	    [](float a, float b) {
		    std::cout << a << " + " << b << " = " << a + b << std::endl;
		    return 0;
	    },
	    arg1, arg2);

	sub_command.add_usage(
	    [](float a, float b) {
		    std::cout << a << " - " << b << " = " << a - b << std::endl;
		    return 0;
	    },
	    arg1, arg2);

	mul_command.add_usage(
	    [](float a, float b) {
		    std::cout << a << " * " << b << " = " << a * b << std::endl;
		    return 0;
	    },
	    arg1, arg2);

	div_command.add_usage(
	    [](float a, float b) {
		    std::cout << a << " / " << b << " = " << a / b << std::endl;
		    return 0;
	    },
	    arg1, arg2);

	program.add_subcommand(std::move(add_command));
	program.add_subcommand(std::move(sub_command));
	program.add_subcommand(std::move(mul_command));
	program.add_subcommand(std::move(div_command));

	return program.run(argc, argv);
}