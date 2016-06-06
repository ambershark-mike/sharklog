cmake_minimum_required(VERSION 3.2)
project(unittest)

find_package(Qt5Core REQUIRED)
find_package(Qt5Test REQUIRED)

include_directories(
	src
	../lib/sharkcore
	)

set(SRCS
	src/main.cpp
	src/test.cpp
	)

add_executable(unittest ${SRCS})
qt5_use_modules(unittest Core Test)

if (NOT NOCRYPT)
	target_link_libraries(unittest sharkcore sharkcrypt)
else()
	target_link_libraries(unittest sharkcore)
endif()

