cmake_minimum_required(VERSION 3.22)
project(lab01)

add_compile_options(-Wall -Wextra)
add_link_options(-Wall -Wextra)

add_definitions(-DLOCAL)
set(CMAKE_CXX_STANDARD 17)

add_executable(lab01 Exp.h TestExp.cpp Consts.h)
