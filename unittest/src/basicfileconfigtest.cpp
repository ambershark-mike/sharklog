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

#include "basicfileconfigtest.h"
#include "basicfileconfig.h"
#include "level.h"

using namespace sharklog;

TEST_F(BasicFileConfigTest, NormalConfigureWorks)
{
	BasicFileConfig::configure(testFile_);
	ASSERT_TRUE(Logger::rootLogger()->outputters().size() == 1);
	ASSERT_TRUE(Logger::rootLogger()->layout() != NULL);
	ASSERT_TRUE(testFileExists());
}

TEST_F(BasicFileConfigTest, NormalConfigureWorksWithLevel)
{
	BasicFileConfig::configure(testFile_, Level::error());
	ASSERT_TRUE(Logger::rootLogger()->outputters().size() == 1);
	ASSERT_TRUE(Logger::rootLogger()->layout() != NULL);
	ASSERT_TRUE(testFileExists());
	ASSERT_TRUE(Logger::rootLogger()->level() == Level::error());
}

TEST_F(BasicFileConfigTest, ConfigReturnsFalseOnEmptyPath)
{
	ASSERT_FALSE(BasicFileConfig::configure(""));
}

TEST_F(BasicFileConfigTest, NamedConfigureWorks)
{
	const char *name = "test";
	BasicFileConfig::configure(testFile_, name);
	ASSERT_TRUE(Logger::logger(name)->outputters().size() == 1);
	ASSERT_TRUE(Logger::logger(name)->layout() != NULL);
	ASSERT_TRUE(testFileExists());
}

TEST_F(BasicFileConfigTest, NamedConfigureWorksWithLevel)
{
	const char *name = "test";
	BasicFileConfig::configure(testFile_, name, Level::error());
	ASSERT_TRUE(Logger::logger(name)->outputters().size() == 1);
	ASSERT_TRUE(Logger::logger(name)->layout() != NULL);
	ASSERT_TRUE(testFileExists());
	ASSERT_TRUE(Logger::logger(name)->level() == Level::error());
}

TEST_F(BasicFileConfigTest, OverloadedConfigReturnsFalseOnEmptyPath)
{
	ASSERT_FALSE(BasicFileConfig::configure("", "test"));
}
