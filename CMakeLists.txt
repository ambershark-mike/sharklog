cmake_minimum_required(VERSION 3.2)

enable_testing()

find_package(GTest)
if (NOT GTEST_FOUND)
	message("No google test was found, will not build test code")
endif()

if (NOT CMAKE_BUILD_TYPE)
	message(STATUS "Defaulting to release mode build, set
	CMAKE_BUILD_TYPE=Debug to change to debug")
	set(CMAKE_BUILD_TYPE "Release")
endif()

# set lib type
if (NOT LIBTYPE)
	message("Libtype is SHARED, use -DLIBTYPE=STATIC to change to static")
	set(LIBTYPE "SHARED")
endif()

message(STATUS "Setting output library type to ${LIBTYPE}")

if (LIBTYPE STREQUAL "STATIC")
    add_definitions("-DSHARKLOG_STATIC")
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin")
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin")

	# check for link type, default is /MD
	if (VS_LINK_MT)
		message(STATUS "Building with /MT (/MTd debug)")
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	else()
		message(STATUS "Building with /MD (/MDd debug)")
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
	endif()
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall --std=c++11 -fPIC")
endif()

# documentation
find_package(Doxygen)
if (DOXYGEN_FOUND)
    add_custom_target(docs DEPENDS sharklog_docs)
endif()

# projects to build
add_subdirectory(lib)
add_subdirectory(loggertest)

if (GTEST_FOUND)
	add_subdirectory(unittest)
	add_test(unittest bin/unittest)
endif()
