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

#include "basicconfigtest.h"
#include "basicconfig.h"

using namespace sharklog;

TEST_F(BasicConfigTest, BasicConfigureWorks)
{
	BasicConfig::configure();
	auto root = Logger::rootLogger();
	ASSERT_TRUE(root->outputters().size() == 1);
    ASSERT_TRUE(root->isValid());
}

TEST_F(BasicConfigTest, LevelConfigWorks)
{
	BasicConfig::configure(Level::error());
	auto root = Logger::rootLogger();
	ASSERT_TRUE(root->outputters().size() == 1);
    ASSERT_TRUE(root->isValid());
	ASSERT_TRUE(root->level() == Level::error());
}

TEST_F(BasicConfigTest, NameConfigureWorks)
{
	const char *name = "test";
	BasicConfig::configure(name);
	auto logger = Logger::logger(name);
	ASSERT_TRUE(logger->isValid());
	ASSERT_TRUE(logger->outputters().size() == 1);
}

TEST_F(BasicConfigTest, NameAndLevelWorks)
{
	const char *name = "test2";
	BasicConfig::configure(name, Level::fatal());
	auto logger = Logger::logger(name);
	ASSERT_TRUE(logger->isValid());
	ASSERT_TRUE(logger->outputters().size() == 1);
	ASSERT_TRUE(logger->level() == Level::fatal());
}
