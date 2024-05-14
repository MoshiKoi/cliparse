#include "../include/cliparse.hpp"

#include <array>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Basic") {
	cli::Command command{"command", "description"};
	command.add_usage([]() -> int { return 0; });
	command.run(1, std::array{"command.exe"}.data());
}