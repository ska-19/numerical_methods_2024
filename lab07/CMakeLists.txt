cmake_minimum_required(VERSION 3.22)
project(lab07)

add_compile_options(-Wall -Wextra)
add_link_options(-Wall -Wextra)

add_definitions(-DLOCAL)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(SOURCE_FILES Consts.h Observer.h Over-all integretor.h RHS.h TimeStepperRKF45.h)

add_executable(lab07 ${SOURCE_FILES})