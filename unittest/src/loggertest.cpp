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

#include "loggertest.h"
#include "logger.h"
#include <iostream>

using namespace sharklog;
using namespace std;

LoggerTest::LoggerTest()
{
}

LoggerTest::~LoggerTest()
{
}

void LoggerTest::SetUp()
{
}

void LoggerTest::TearDown()
{
    Logger::closeRootLogger();
}

TEST_F(LoggerTest, HasRootLogger)
{
    ASSERT_TRUE((bool)Logger::rootLogger());
}

TEST_F(LoggerTest, RootLoggerIsTaggedAsRoot)
{
    ASSERT_TRUE(Logger::rootLogger()->isRoot());
}

TEST_F(LoggerTest, RootLoggerIsNameless)
{
    ASSERT_TRUE(Logger::rootLogger()->name().empty());
}

TEST_F(LoggerTest, CloseRootWorks)
{
    auto oldRoot = Logger::rootLogger();
    oldRoot->closeRootLogger();
    ASSERT_NE(oldRoot, Logger::rootLogger());
}

TEST_F(LoggerTest, CloseRootCleansChildren)
{
    Logger::logger("x.y.z");
    ASSERT_EQ(4, Logger::count());
    
    Logger::closeRootLogger();
    
    ASSERT_EQ(0, Logger::count());
}

TEST_F(LoggerTest, RootHasNoParent)
{
    ASSERT_FALSE((bool)Logger::rootLogger()->parent());
}

TEST_F(LoggerTest, GetANamedLoggerWorks)
{
    ASSERT_TRUE((bool)Logger::logger("test"));
}

TEST_F(LoggerTest, NamedLoggerNameMatches)
{
    ASSERT_STREQ("test", Logger::logger("test")->name().c_str());
}

TEST_F(LoggerTest, SimpleNameLoggerParentIsRoot)
{
    //FAIL() << "test name " << test->name() << " parent name " << test->parent()->name() << " parent is root " << test->parent()->isRoot()
        //<< " stored root ptr " << root << " root pointer " << Logger::rootLogger() << " test ptr " << test << " test parent ptr " << test->parent();
    ASSERT_EQ(Logger::logger("test")->parent(), Logger::rootLogger());
}

TEST_F(LoggerTest, GetNamedLoggerThatExists)
{
    auto logger = Logger::logger("test");
    EXPECT_TRUE((bool) logger);
    ASSERT_EQ(logger, Logger::logger("test"));
}

TEST_F(LoggerTest, EmptyNameLoggerGetsRoot)
{
    ASSERT_TRUE(Logger::logger("")->isRoot());
}

TEST_F(LoggerTest, BaseAndFullNameAreTheSame)
{
    auto log = Logger::logger("test");
    ASSERT_STREQ("test", log->name().c_str());
    ASSERT_STREQ("test", log->baseName().c_str());
}

TEST_F(LoggerTest, BaseAndFullNameAreDifferent)
{
    auto log = Logger::logger("com.ambershark");
    ASSERT_STREQ("com.ambershark", log->name().c_str());
    ASSERT_STREQ("ambershark", log->baseName().c_str());
}

TEST_F(LoggerTest, BaseNameIsOkWithMultiTier)
{
    auto log = Logger::logger("com.ambershark.sharklog");
    ASSERT_STREQ("sharklog", log->baseName().c_str());
}

TEST_F(LoggerTest, BaseNameOkEndingWithPeriod)
{
    auto log = Logger::logger("com.");
    ASSERT_STREQ("com", log->baseName().c_str());
}

TEST_F(LoggerTest, ExtraPeriodsAreStrippedFromName)
{
    auto log = Logger::logger(".x..y.z...");
    ASSERT_STREQ("x.y.z", log->name().c_str());
}

TEST_F(LoggerTest, BaseIsOkWithOnlyAPeriodInName)
{
    auto log = Logger::logger(".");
    ASSERT_STREQ("", log->name().c_str());
    ASSERT_STREQ("", log->baseName().c_str());
    ASSERT_EQ(log, Logger::rootLogger());
}

TEST_F(LoggerTest, BaseNameIsOkWithMultipleDots)
{
    auto log = Logger::logger("..");
    ASSERT_STREQ("", log->baseName().c_str());
    ASSERT_STREQ("", log->name().c_str());
    
    log = Logger::logger("...");
    ASSERT_STREQ("", log->baseName().c_str());
    ASSERT_STREQ("", log->name().c_str());
}

TEST_F(LoggerTest, TestSingleCharName)
{
    auto log = Logger::logger("x");
    ASSERT_STREQ("x", log->baseName().c_str());
}

TEST_F(LoggerTest, TestLongNameWithSpaces)
{
    const char *name = "testing a long name with spaces";
    auto log = Logger::logger(name);
    ASSERT_STREQ(name, log->name().c_str());
    ASSERT_STREQ(name, log->baseName().c_str());
}

TEST_F(LoggerTest, HasCreatedNamedLogger)
{
    Logger::logger("test");
    ASSERT_TRUE(Logger::hasLogger("test"));
    
    Logger::logger("mike.is.cool");
    ASSERT_TRUE(Logger::hasLogger("mike"));
    ASSERT_TRUE(Logger::hasLogger("mike.is"));
    ASSERT_TRUE(Logger::hasLogger("mike.is.cool"));
}

TEST_F(LoggerTest, LoggerCountIsZero)
{
    ASSERT_EQ(0, Logger::count());
}

TEST_F(LoggerTest, LoggerCountIsOne)
{
    ASSERT_EQ(1, Logger::rootLogger()->count());
}

TEST_F(LoggerTest, CloseChildLoggerKeepsParents)
{
    Logger::logger("ab.cd.ef");
    ASSERT_TRUE(Logger::hasLogger("ab.cd.ef"));
    ASSERT_TRUE(Logger::hasLogger("ab"));
    ASSERT_EQ(4, Logger::count());
    
    Logger::closeLogger(Logger::logger("ab.cd.ef"));
    ASSERT_EQ(3, Logger::count());
    
    Logger::closeLogger(Logger::logger("ab.cd"));
    ASSERT_EQ(2, Logger::count());
}

TEST_F(LoggerTest, CloseParentClosesAllChildren)
{
    Logger::logger("x1.2.3");
    EXPECT_TRUE(Logger::hasLogger("x1.2.3"));
    EXPECT_TRUE(Logger::hasLogger("x1"));
    
    Logger::closeLogger(Logger::logger("x1.2"));
    EXPECT_EQ(2, Logger::count());
    ASSERT_FALSE(Logger::hasLogger("x1.2.3"));
    ASSERT_FALSE(Logger::hasLogger("x1.2"));
}

TEST_F(LoggerTest, ClosingAndMakingANewLoggerWorks)
{
    auto old = Logger::logger("xy.zzy");
    EXPECT_TRUE((bool)old);
    
    Logger::closeLogger(old);
    EXPECT_FALSE(Logger::hasLogger("xy.zzy"));
    
    auto n = Logger::logger("xy.zzy");
    EXPECT_TRUE((bool)n);
    
    ASSERT_NE(old, n);
}

TEST_F(LoggerTest, DISABLED_LoggerNamesAreCaseInsensitive)
{
    auto logger = Logger::logger("Mike");
    EXPECT_TRUE((bool)logger);
    ASSERT_EQ(logger, Logger::logger("mike"));
}
