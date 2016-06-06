cmake_minimum_required(VERSION 3.2)

if (NOT CMAKE_BUILD_TYPE)
	message(STATUS "Defaulting to release mode build, set
	CMAKE_BUILD_TYPE=Debug to change to debug")
	set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall --std=c++11")

add_subdirectory(lib)
add_subdirectory(unittest)

