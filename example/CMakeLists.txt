cmake_minimum_required(VERSION 3.22)
project(minimal_uuid4)

set(CMAKE_CXX_STANDARD 11)

include_directories(../include)
add_executable(minimal_uuid4 example.cpp)
