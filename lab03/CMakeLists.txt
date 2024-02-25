cmake_minimum_required(VERSION 3.22)
project(lab03)

add_compile_options(-Wall -Wextra)
add_link_options(-Wall -Wextra)

add_definitions(-DLOCAL)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(SOURCE_FILES Exp.h Exp_Chebyshev.h TestExp.cpp Consts.h)

add_executable(lab03 ${SOURCE_FILES})

find_package(GSL REQUIRED)
target_link_libraries(lab03 GSL::gsl)
