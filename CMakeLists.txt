cmake_minimum_required(VERSION 3.26)
project(CliParse)
set(CMAKE_CXX_STANDARD 20)

include(CTest)
add_subdirectory(tests)

if (CLIPARSE_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

add_library(cli INTERFACE "include/cliparse.hpp")