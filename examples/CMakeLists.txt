include_directories("../include")

add_executable(add add_program.cpp)
add_executable(calc calc_program.cpp)
add_executable(calc2 calc2_program.cpp)
add_executable(cat cat_program.cpp)

target_link_libraries(add INTERFACE cli)
target_link_libraries(calc INTERFACE cli)
target_link_libraries(calc2 INTERFACE cli)
target_link_libraries(cat INTERFACE cli)