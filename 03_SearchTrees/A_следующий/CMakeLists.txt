cmake_minimum_required(VERSION 3.15)
project(A_)


set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -fsanitize=address")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
set(CMAKE_CXX_STANDARD 17)

add_executable(A_ main.cpp)