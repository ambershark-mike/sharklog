////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2016, by Ambershark, LLC.
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

#include "loggerstreamtest.h"
#include "loggerstream.h"
#include <string>

using namespace sharklog;
using namespace std;

TEST_F(LoggerStreamTest, ConstructorSetupWorks)
{
    LoggerStream ls(Logger::rootLogger(), Level::fatal());
    ASSERT_TRUE(ls.level() == Level::fatal());
    ASSERT_TRUE(ls.logger() == Logger::rootLogger());
}

TEST_F(LoggerStreamTest, ConstructorDefaultSetupOk)
{
    LoggerStream ls;
    ASSERT_TRUE(ls.level() == Level::trace());
    ASSERT_TRUE(ls.logger() == Logger::rootLogger());
}

TEST_F(LoggerStreamTest, TestLogOfInt)
{
    LoggerStream ls;
    ls << 10;
    ASSERT_STREQ("10", ls.data().c_str());
}

TEST_F(LoggerStreamTest, TestMultipleItemStreaming)
{
    LoggerStream ls;
    ls << "test double " << (double)3.14159;
    ls << " test string " << std::string("mystring");
    ASSERT_STREQ("test double 3.14159 test string mystring", ls.data().c_str());
}

TEST_F(LoggerStreamTest, StreamingLevelChangesLevel)
{
    LoggerStream ls;
    EXPECT_TRUE(ls.level() == Level::trace());
    
    ls << Level::info();
    ASSERT_TRUE(ls.level() == Level::info());
}

TEST_F(LoggerStreamTest, ConstructorWithNameWorks)
{
    LoggerStream ls("test");
    ASSERT_TRUE(ls.level() == Level::trace());
    ASSERT_TRUE(ls.logger() == Logger::logger("test"));
}

TEST_F(LoggerStreamTest, LocationStreamingWorks)
{
    LoggerStream ls;
    //ls << Location();
}
