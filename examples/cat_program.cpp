#include <fstream>
#include <iostream>

#include "cliparse.hpp"

int
main(int argc, char const **argv) {
	cli::Command program{"cat", "Print the contents of a file"};

	cli::Argument<char const *> filename_arg{"file", "File to print"};

	program.add_usage(
	    [](char const *filename) {
			std::fstream fs {filename};
		    std::cout << fs.rdbuf();
		    return 0;
	    },
	    filename_arg);

	return program.run(argc, argv);
}