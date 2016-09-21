cmake_minimum_required(VERSION 3.2)
project(unittest)

include_directories(
	src
	../lib/sharklog
	)

set(SRCS
	src/main.cpp
	src/loggertest.cpp
    src/utilfunctionstest.cpp
	src/utilfunctionstest.h
	src/leveltest.cpp
	src/leveltest.h
	src/layouttest.cpp
	)

add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} sharklog /usr/lib/libgtest.so)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

