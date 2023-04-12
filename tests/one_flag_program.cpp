#include "cliparse.hpp"
#include "cliparse/command.hpp"
#include "cliparse/option.hpp"

int
main(int argc, char const **argv) {
	cli::Command program{"one_flag_program", "description"};

	cli::Option<bool> my_flag{"flag", "description"};

	program.add_usage([](bool) { return 0; }, my_flag);

	program.run(argc, argv);
}