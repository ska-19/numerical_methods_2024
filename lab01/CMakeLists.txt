cmake_minimum_required(VERSION 3.22)
project(numerical_methods_2024)

add_compile_options(-Wall -Wextra)
add_link_options(-Wall -Wextra)

add_definitions(-DLOCAL)
set(CMAKE_CXX_STANDARD 17)

add_executable(numerical_methods_2024 main.cpp Exp.cpp Exp.h)


