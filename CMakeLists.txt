cmake_minimum_required(VERSION 3.2)
project(MultiprocessorSchedulingProblem)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(googletest)
include_directories(googletest/googletest/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
include_directories(src)

set(SOURCE_FILES src src/test.cpp)

add_executable(MultiprocessorSchedulingProblem ${SOURCE_FILES})
target_link_libraries(MultiprocessorSchedulingProblem gtest gtest_main)
