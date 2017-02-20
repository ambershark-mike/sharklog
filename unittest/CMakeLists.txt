cmake_minimum_required(VERSION 3.2)
project(unittest)

include_directories(
	src
	../lib/sharklog
    ../lib
	${GTEST_INCLUDE_DIRS}
	)

set(SRCS
	src/main.cpp
	src/loggertest.cpp
    src/utilfunctionstest.cpp
	src/utilfunctionstest.h
	src/leveltest.cpp
	src/leveltest.h
	src/layouttest.cpp
	src/standardlayouttest.cpp
	src/standardlayouttest.h
	src/outputtertest.cpp
	src/consoleoutputtertest.cpp
	src/consoleoutputtertest.h
	src/loggerstreamtest.cpp
	src/loggerstreamtest.h
	src/locationtest.cpp
	src/fileoutputtertest.cpp
	src/fileoutputtertest.h
	src/functracetest.cpp
	src/basicconfigtest.h
	src/basicconfigtest.cpp
	src/basicfileconfigtest.h
	src/basicfileconfigtest.cpp
	)

add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} sharklog ${GTEST_LIBRARIES})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

