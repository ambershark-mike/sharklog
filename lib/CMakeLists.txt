cmake_minimum_required(VERSION 3.2)
project(sharklog)

# version
set(sharklog_VERSION_MAJOR 0)
set(sharklog_VERSION_MINOR 1)
set(sharklog_VERSION_MAINT 0)
set(sharklog_VERSION_STRING
	${sharklog_VERSION_MAJOR}.${sharklog_VERSION_MINOR}.${sharklog_VERSION_MAINT}
	)
add_definitions("-DSHARKLOG_VERSION=${sharklog_VERSION_STRING}")

# set lib type
if (NOT LIBTYPE)
	message("Libtype is SHARED, use -DLIBTYPE=STATIC to change to static")
	set(LIBTYPE "SHARED")
endif()

message(STATUS "Setting output library type to ${LIBTYPE}")

# source files
include_directories(
	sharklog
	)

set(SRCS
	sharklog/logger.cpp
    sharklog/logger.h
    sharklog/utilfunctions.cpp
	sharklog/utilfunctions.h
	)

# build
add_library(${PROJECT_NAME} ${LIBTYPE} ${SRCS})
set_target_properties(${PROJECT_NAME} PROPERTIES 
	VERSION ${sharklog_VERSION_STRING}
	SOVERSION ${sharklog_VERSION_STRING}
	)

# docs
if (DOXYGEN_FOUND)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in
		${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY
		)

	add_custom_target(
		sharklog_docs
		${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
		COMMENT "Enabling docuemntation build, build with make sharklog_docs"
		)
else()
	message(WARNING "No doxygen installed, can't make documentation")
endif()

# installation
message(STATUS "Install prefix path set to ${CMAKE_INSTALL_PREFIX}")

install(
	TARGETS ${PROJECT_NAME} 
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	)

install(
	DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/sharklog/
	DESTINATION include/sharklog
	FILES_MATCHING PATTERN "*.h"
	)

install(
	DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html/
	DESTINATION share/doc/sharklog
	FILES_MATCHING PATTERN "*.*"
	)

