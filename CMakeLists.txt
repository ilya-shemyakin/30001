cmake_minimum_required(VERSION 3.26)
project(melnikov_vladimir)

set(CMAKE_CXX_STANDARD 14)

include_directories(melnikov.vladimir/T2)

add_executable(melnikov_vladimir
        melnikov.vladimir/T2/main.cpp
)
