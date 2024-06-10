cmake_minimum_required(VERSION 3.22)
project(lab05)

add_compile_options(-Wall -Wextra)
add_link_options(-Wall -Wextra)

add_definitions(-DLOCAL)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(SOURCE_FILES Differentiator.h TestDifferentiator.cpp
        AAD22.h)

add_executable(lab05 ${SOURCE_FILES})

#find_package(GSL REQUIRED)
#target_link_libraries(lab05 GSL::gsl)
