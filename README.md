
## Overview

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

## Release Notes

#### 0.1

- This release only tested/working with OSX and Linux, no windows support yet (sorry, my least favorite platform)
- The basic Logger system (supporting multi-level named loggers)
- StandardLayout (a basic/standard layout for messages)
- ConsoleOutputter (outputs log messages to the console)
- Synchronous thread-safe logging
- A simple loggertest application (including thread testing)

#### 0.2

- File outputter via \ref sharklog::FileOutputter
- Logging macros, \ref SHARKLOG_TRACE, etc
- Logger streaming via \ref sharklog::LoggerStream
- Version checking interface into Logger, see \ref sharklog::Logger::version()
- Function tracing, using \ref sharklog::FuncTrace or \ref SHARKLOG_FUNCTRACE you can now trace enter and exit of functions
- Better documentation / examples

## Upcoming Version Plans

#### 0.3
- Configuration system (files, command line parameters, classes)
- Custom/Patterned Layout
- Windows support (mingw and visual c++)

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

## Requirements

Linux: 

- cmake 3.2+
- g++ with c++11 support (tested with 6.2.1)
- Google Test (gtest) (optional, to run tests, tested with 1.7.0)

## License

Copyright (c) 2016 Ambershark, LLC.

Released under the L-GPL license available at http://www.gnu.org/licenses/lgpl.html.

See \ref copying, or the COPYING.dox file.

## Building

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

Not supported yet.

#### MinGW

Not supported yet.

## Using the Library

TODO: for now see \ref sharklog::Logger.

## Author

Written by Mike Ryan (<public@ambershark.com>).

## Contributors

