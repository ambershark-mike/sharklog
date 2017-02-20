cmake_minimum_required(VERSION 3.2)
project(loggertest)

include_directories(
	src
	../lib/sharklog
    ../lib
	)

set(SRCS
	src/main.cpp
	)

add_executable(${PROJECT_NAME} ${SRCS})

if (MSVC)
    target_link_libraries(${PROJECT_NAME} sharklog)
else()
	target_link_libraries(${PROJECT_NAME} sharklog pthread)
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

