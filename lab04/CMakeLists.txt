cmake_minimum_required(VERSION 3.22)
project(lab04)

add_compile_options(-Wall -Wextra)
add_link_options(-Wall -Wextra)

add_definitions(-DLOCAL)
set(CMAKE_CXX_STANDARD 17)

add_executable(lab04 Exp.h TestExp.cpp Consts.h)

find_package(GSL REQUIRED)
target_link_libraries(lab04 GSL::gsl)
