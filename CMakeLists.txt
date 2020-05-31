cmake_minimum_required(VERSION 3.15)
project(NFA)

set(CMAKE_CXX_STANDARD 14)

add_executable(NFA main.cpp NFA.h NFA1.cpp NFA.cpp)