
## Overview

Sharklog is a powerful and fast logging library written in C++ for use in C++ applications.  It can be used on multiple platforms including, linux, windows (visual c++), windows (mingw), and OSX.  It can be built for the ARM processor and used on the Android platform as well.  In the future iOS will be supported as well.

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

@code
$ mkdir build
$ cd build
$ cmake ..
$ make
@endcode

To build the documentation (follow above build then do):

@code
$ make docs
@endcode

To run the tests (assuming google test is installed, also following steps above):

@code
$ make test
... alternatively if you want the full test run
$ ./bin/unittest
@endcode

### Mac OSX

To build the library:

@code
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
@endcode

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

