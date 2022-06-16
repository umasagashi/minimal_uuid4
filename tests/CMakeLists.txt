cmake_minimum_required(VERSION 3.22)
project(minimal_uuid4)

set(CMAKE_CXX_STANDARD 14)

include_directories(../include)

enable_testing()

add_executable(test_runner test_runner.cpp)
add_test(NAME test COMMAND test_runner)
