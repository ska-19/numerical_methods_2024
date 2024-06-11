cmake_minimum_required(VERSION 3.22)
project(lab06)



add_definitions(-DLOCAL)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(SOURCE_FILES TestSam.cpp)

add_executable(lab06 TestSam.cpp)
add_executable(lab06_pg PG.h Consts.h SAM.h TestPG.cpp)
find_package(GSL REQUIRED)
target_link_libraries(lab06 GSL::gsl)
target_link_libraries(lab06_pg GSL::gsl)