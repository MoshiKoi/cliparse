include_directories("../include")

add_executable(add add_program.cpp)

target_link_libraries(add INTERFACE cli)