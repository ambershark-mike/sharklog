cmake_minimum_required(VERSION 3.2)
project(sharkcore)

enable_testing()

# set release as default
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

# version
set(sharkcore_VERSION_MAJOR 1)
set(sharkcore_VERSION_MINOR 8)
set(sharkcore_VERSION_MAINT 0)
set(sharkcore_VERSION_STRING
	${sharkcore_VERSION_MAJOR}.${sharkcore_VERSION_MINOR}.${sharkcore_VERSION_MAINT}
	)

# packages
find_package(Qt5Core REQUIRED)
find_package(Doxygen)

# set lib type
if (NOT LIBTYPE)
	message("Libtype is SHARED, use -DLIBTYPE=STATIC to change to static")
	set(LIBTYPE "SHARED")
endif()

message(STATUS "Setting output library type to ${LIBTYPE}")

if (NOCRYPT)
	message(STATUS "Building without crypto support")
	add_definitions(-DNOCRYPT)
else()
	message(STATUS "Including crypto support from sharkcrypt")
endif()

# source files
include_directories(
	sharkcore
	)

set(SRCS
	sharkcore/commandlineparser.cpp
	sharkcore/documentbundle.cpp
	sharkcore/errormanager.cpp
	sharkcore/logger.cpp
	sharkcore/loggerstreamhandler.cpp
	sharkcore/networkpacket.cpp
	sharkcore/parser.cpp
	sharkcore/poolthread.cpp
	sharkcore/recentfilelist.cpp
	sharkcore/safeoutput.cpp
	sharkcore/threadpool.cpp
	sharkcore/threadwait.cpp
	)

# build
add_library(${PROJECT_NAME} ${LIBTYPE} ${SRCS})
set_target_properties(${PROJECT_NAME} PROPERTIES 
	VERSION ${sharkcore_VERSION_STRING}
	SOVERSION ${sharkcore_VERSION_STRING}
	)
qt5_use_modules(${PROJECT_NAME} Core)

# docs
if (DOXYGEN_FOUND)
	add_custom_target(
		sharkcore_docs
		${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile
		COMMENT "Enabling docuemntation build, build with make sharkcore_docs"
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
	DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/sharkcore/
	DESTINATION include/sharkcore
	FILES_MATCHING PATTERN "*.h"
	)

install(
	DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html/
	DESTINATION share/doc/sharkcore
	FILES_MATCHING PATTERN "*.*"
	)

