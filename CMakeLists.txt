cmake_minimum_required(VERSION 3.2)

enable_testing()

# TODO: add a check for gtest
#find_package(gtest)

if (NOT CMAKE_BUILD_TYPE)
	message(STATUS "Defaulting to release mode build, set
	CMAKE_BUILD_TYPE=Debug to change to debug")
	set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall --std=c++11")

add_subdirectory(lib)
add_subdirectory(unittest)

# TODO: add check for if gtest is found
add_test(unittest bin/unittest)
