////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2017, by Ambershark, LLC.
//
// Distributed under the L-GPL license.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You sould have received a copy of the GNU Lesser General Public
// License along with this program.  If not see
// <http://www.gnu.org/licenses>.
//
// This notice must remain in the source code and any derived source.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef basicfileconfigtest_H
#define basicfileconfigtest_H

#include <gtest/gtest.h>
#include <cstdio>
#include "logger.h"
#include <fstream>

class BasicFileConfigTest : public ::testing::Test
{
protected:
	BasicFileConfigTest()
	{
	}

	virtual ~BasicFileConfigTest()
	{
	}

	bool testFileExists()
	{
		std::ifstream file(testFile_);
		return file.good();
	}

	virtual void SetUp()
	{
		sharklog::Logger::closeRootLogger();
	}

	virtual void TearDown()
	{
		sharklog::Logger::closeRootLogger();
		remove(testFile_);
	}

	const char *testFile_ = "sharklog-test-file";
}; 

#endif /* basicfileconfigtest_H */

