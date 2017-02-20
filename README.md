## Overview

## Table of Contents

- [Overview](#overview)
- [Release Notes](#relnotes)
- [Future Plans](#future)
- [Requirements](#reqs)
- [License](#license)
- [Building](#building)
- [Including Sharklog Libraries In Your Project](#including)
- [Using the Library](#using)
- [Credits](#credits)

## <a name="overview"></a>Overview

Sharklog is a powerful and fast logging library written in C++ for use in C++ applications.  It can be used on multiple platforms including, linux, windows (visual c++), windows (mingw), and OSX.  It can be built for the ARM processor and used on the Android platform as well.  In the future iOS will be supported as well.

So why write yet another logging library?

Well, I never quite found a logging library that fit completely with my style.  The closest one was Apache's log4cxx, however this library is huge and has a lot of dependencies.  I find it increasingly more difficult to get it to build with Windows due to the Apache libs dependencies.  Some just wouldn't build under certain versions of MinGW or Visual C++.  It was always a struggle.  So while I really like log4cxx I just kind of gave up on supporting my code that used it and decided to write my own logger.

I designed this logger to be easy to use (as I believe log4cxx is), fast, and most importantly easy to build and maintain on all supported platforms.

I don't intend to mirror all the features of log4cxx (maybe some day, but definitely not now), but I am planning on including the support for what I view as the most popular parts.  I'm not copying anything from log4cxx but am loosely basing my design on theirs.  I really like the idea of Appenders/Layouts/Configurators/etc.  It makes the logging library very versatile and expandable.

This project is in it's infancy and as of this release (0.2) it has limited support.  It is however a fully functional synchronous (blocking) logger.  There are now interfaces for logging streams as well as logging macros.  You can use the following macros:
    - \ref SHARKLOG_DEBUG
    - \ref SHARKLOG_TRACE
    - \ref SHARKLOG_INFO
    - \ref SHARKLOG_WARN
    - \ref SHARKLOG_ERROR
    - \ref SHARKLOG_FATAL
    
These macros will be fast.  In a situation where the logger is off for a specific level there is only the single *if* check to see if the logger is enabled.  If not nothing else happens.

Logger streaming is now available as well.  You can use the \ref sharklog::LoggerStream class do handle logging in a C++ stream manner.
    
The entire logger has been and will continue to be written with TDD using google test.  I am aiming for 90% or better code coverage with unit tests, to make sure the library stays stable and crash free.

## <a name="relnotes"></a>Release Notes

#### 0.3
- Added a BasicConfig class that sets up a basic console logger automatically
- Added a BasicFileConfig class that sets up sa basic file logger automatically
- Fixed time functions to work with gcc 4 (no longer is gcc 5 required to build)
- Updated documentation for all classes, finished incomplete docs
- Added ability to set Level's by text name with Level::name("debug") function

#### 0.2

- File outputter via \ref sharklog::FileOutputter
- Logging macros, \ref SHARKLOG_TRACE, etc
- Logger streaming via \ref sharklog::LoggerStream
- Version checking interface into Logger, see \ref sharklog::Logger::version()
- Function tracing, using \ref sharklog::FuncTrace or \ref SHARKLOG_FUNCTRACE you can now trace enter and exit of functions
- Better documentation / examples

#### 0.1

- This release only tested/working with OSX and Linux, no windows support yet (sorry, my least favorite platform)
- The basic Logger system (supporting multi-level named loggers)
- StandardLayout (a basic/standard layout for messages)
- ConsoleOutputter (outputs log messages to the console)
- Synchronous thread-safe logging
- A simple loggertest application (including thread testing)

## <a name="future"></a>Upcoming Version Plans

#### Future Versions

- Log file rotation
- Asynchronous logging
- HTML layout
- XML layout
- syslog Outputter
- Encrypted/secure Outputter
- tcp/ip outputter
- Performance tuning
- Better documentation / examples
- vagrant support for building
- Android support including JNI interfaces
- iOS support with objective-c/swift interfaces

## <a name="reqs"></a>Requirements

Linux: 

- cmake 3.2+
- g++ with c++11 support (tested with 6.2.1 and 4.9.4)
- Google Test (gtest) (optional, to run tests, tested with 1.7.0)

## <a name="license"></a>License

Copyright (c) 2016-17 Ambershark, LLC.

Released under the L-GPL license available at http://www.gnu.org/licenses/lgpl.html.

See \ref copying, or the COPYING.dox file.

## <a name="building"></a>Building

### Linux

To build the library:

~~~~~~~~~~~~~~~~~~~~~~~
$ mkdir build
$ cd build
$ cmake ..
$ make
~~~~~~~~~~~~~~~~~~~~~~~

To build the documentation (follow above build then do):

~~~~~~~~~~~~~~~~~~~~~~~
$ make docs
~~~~~~~~~~~~~~~~~~~~~~~

To run the tests (assuming google test is installed, also following steps above):

~~~~~~~~~~~~~~~~~~~~~~~
$ make test
... alternatively if you want the full test run
$ ./bin/unittest
~~~~~~~~~~~~~~~~~~~~~~~

### Mac OSX

To build the library:

~~~~~~~~~~~~~~~~~~~~~~~
$ mkdir build
$ cd build
$ cmake ..
$ make
.. build docs with
$ make docs
.. run test with
$ make test
.. or ..
$ ./bin/unittest
~~~~~~~~~~~~~~~~~~~~~~~

### Windows

#### Visual C++

**Using Vagrant**: There is a Vagrantfile in the root of the project that will set up a build environment for you.  It uses a custom box, but you can use any Windows 10 Pro base box that you'd like.

Requirements:
* CMake 3.2+ (choco install -y cmake)
* Visual Studio or vc build tools (choco install -y vcbuildtools)

Run MSBuild capable cmd, i.e. c:\program files (x86)\Microsoft Visual C++ Build Tools\Visual C++ 2015 MSBuild Command Prompt.

Note: To get this I installed the build tools only (no visual studio) with chocolatey command "choco install vcbuildtools" see sharklog/provision/packages.bat.

**Linking Type /MT or /MD**: The default for the library is /MD and /MDd for debug.  If you want to use /MT or /MTd you need to pass `-DVS_LINK_MT=1` to cmake.  This may be required for Google Test depending on which type of libraries you built for GTest.

**Google Test**: To point cmake at your google test install you need to specify the root path to cmake like so `-DGTEST_ROOT="C:\path\to\googletest"`.  Make sure that inside that path is the *include* and *lib* directories.

~~~~~~~~~~~~~~~~~~~~~~~
> mkdir sharklog-build
> cd sharklog-build
> cmake -G "Visual Studio 14 2015" x:\path\to\sharklog
    I.e. for vagrant: > cmake -G "Visual Studio 14 2015" c:\vagrant
> msbuild Project.sln /t:Build /p:Configuration=Release
~~~~~~~~~~~~~~~~~~~~~~~

#### MinGW

Not supported yet.  Coming in the next release.

## <a name="including"></a>Including the Library In Your Projects

To use the library in your project just include the base directory in your includes for whatever build system you use.  For example using cmake below:

Assuming the library has been installed to /usr/local/include/sharklog, and the libraries installed to /usr/local/lib.  This also assumes /usr/local/lib is in your library path for your build.

```
cmake_minimum_required(VERSION 3.2)
project(yourproject)

include_directories(/usr/local/include)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} sharklog)
```

In the future there will be a cmake detection script for sharklog that will detect where it is installed on your system and set up the libraries and include automatically.

## <a name="using"></a>Using the Library

```
#include <sharklog/standardlayout.h>
#include <sharklog/consoleoutputter.h>
#include <sharklog/logger.h>
#include <sharklog/loggerstream.h>
#include <sharklog/basicconfig.h>

using namespace sharklog;

int main()
{
   // set up logger
   BasicConfig::configure();
   
   // log a message to root
   Logger::rootLogger()->log(Level::trace(), "Hello");
   
   // log a message at trace level to root using a macro
   SHARKLOG_TRACE(Logger::rootLogger(), "this is a trace");
   
   // log a message to root with a stream
   LoggerStream() << "this is also a root trace" << SHARKLOG_END;
}
```

## <a name="credits"></a>Author

Written by Mike Ryan (<public@ambershark.com>).

## Contributors

