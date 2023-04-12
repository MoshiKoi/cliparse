cmake_minimum_required(VERSION 3.26)
project(CliParse)
set(CMAKE_CXX_STANDARD 20)

include(CTest)
add_subdirectory(tests)

add_library(cli INTERFACE "include/cliparse/Command.hpp" "include/cliparse/Argument.hpp")