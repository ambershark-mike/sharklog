////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2016-17, by Ambershark, LLC.
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
#include "standardlayout.h"
#include "consoleoutputter.h"
#include <regex>

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

StringOutputter *LoggerTest::setupMacroTest()
{
    auto logger = Logger::rootLogger();
    auto op = make_shared<StringOutputter>();
    op->setLayout(make_shared<StandardLayout>());
    logger->addOutputter(op);
    return dynamic_cast<StringOutputter *>(logger->outputters().front().get());
}

bool LoggerTest::testMacro(const std::string &type, const std::string &test)
{
    stringstream ss;
    ss << "^\\[[0-9]{2}\\/[0-9]{2}\\/[0-9]{4}\\]\\[[0-9]{2}:[0-9]{2}:[0-9]{2}.[0-9]{3}\\]\\[0x[a-z0-9]{12}\\]\\[" << type << "\\] test\n";
    auto re = regex(ss.str());
    return regex_match(test.c_str(), re);
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

TEST_F(LoggerTest, LoggerNamesAreCaseInsensitive)
{
    auto logger = Logger::logger("Mike IS cool");
    EXPECT_TRUE((bool)logger);
    ASSERT_EQ(logger, Logger::logger("mike is cool"));
}

TEST_F(LoggerTest, SetLevelWorks)
{
    auto logger = Logger::rootLogger();
    logger->setLevel(Level::info());
    ASSERT_TRUE(Level::info() == logger->level()) << logger->level().name();
}

TEST_F(LoggerTest, BaseLoggerNotValid)
{
    ASSERT_FALSE(Logger::rootLogger()->isValid());
}

TEST_F(LoggerTest, RootLoggerIsValidWhenSetUp)
{
    auto op = make_shared<ConsoleOutputter>();
    op->setLayout(make_shared<StandardLayout>());
    Logger::rootLogger()->addOutputter(op);
    ASSERT_TRUE(Logger::rootLogger()->isValid());
}

TEST_F(LoggerTest, AddOutputterWorks)
{
	auto logger = Logger::rootLogger();
	EXPECT_TRUE(logger->outputters().empty());

	auto op = OutputterPtr(new ConsoleOutputter);
	logger->addOutputter(op);
	EXPECT_EQ(1, logger->outputters().size());
	ASSERT_TRUE(logger->outputters().front() == op);
}

TEST_F(LoggerTest, AddingSameOutputterFails)
{
    auto logger = Logger::rootLogger();
    auto op = OutputterPtr(new ConsoleOutputter);
    logger->addOutputter(op);
    EXPECT_EQ(1, logger->outputters().size());
    logger->addOutputter(op);
    ASSERT_EQ(1, logger->outputters().size());
}

TEST_F(LoggerTest, RemoveOutputterWorks)
{
    auto logger = Logger::rootLogger();
    auto op = OutputterPtr(new ConsoleOutputter);
    logger->addOutputter(op);
    EXPECT_TRUE(logger->outputters().size());
    logger->removeOutputter(op);
    ASSERT_TRUE(logger->outputters().empty());
}

TEST_F(LoggerTest, RemoveSameOutputterFails)
{
    auto logger = Logger::rootLogger();
    auto op = OutputterPtr(new ConsoleOutputter);
    logger->addOutputter(op);
    EXPECT_TRUE(logger->outputters().size());
    logger->removeOutputter(op);
    EXPECT_TRUE(logger->outputters().empty());
    
    logger->addOutputter(OutputterPtr(new ConsoleOutputter));
    logger->removeOutputter(op);
    ASSERT_EQ(1, logger->outputters().size());
}

TEST_F(LoggerTest, RootDefaultsToMaxLevel)
{
    ASSERT_TRUE(Logger::rootLogger()->level() == Level::all());
}

TEST_F(LoggerTest, LoggingWithWrongLevelReturnsImmediately)
{
    auto logger = Logger::rootLogger();
    logger->setLevel(Level::fatal());
    ASSERT_FALSE(logger->log(Level::info(), "test"));
}

TEST_F(LoggerTest, LoggingWithNoLayoutFails)
{
    ASSERT_FALSE(Logger::rootLogger()->log(Level::fatal(), "test"));
}

TEST_F(LoggerTest, LoggingWithNoOutputtersFails)
{
    ASSERT_FALSE(Logger::rootLogger()->log(Level::fatal(), "test"));
}

TEST_F(LoggerTest, LoggingWorks)
{
    auto logger = Logger::rootLogger();
    EXPECT_TRUE(logger->outputters().empty());
    
    auto op = make_shared<StringOutputter>();
    op->setLayout(make_shared<StandardLayout>());
    logger->addOutputter(op);
    EXPECT_TRUE(logger->log(Level::fatal(), "this is a test"));
    
    auto sop = dynamic_cast<StringOutputter *>(logger->outputters().front().get());
    auto re = regex("^\\[[0-9]{2}\\/[0-9]{2}\\/[0-9]{4}\\]\\[[0-9]{2}:[0-9]{2}:[0-9]{2}.[0-9]{3}\\]\\[0x[a-z0-9]{12}\\]\\[FATAL\\] this is a test\n");
    ASSERT_TRUE(regex_match(sop->output_.c_str(), re)) << sop->output_.c_str();
}

TEST_F(LoggerTest, DISABLED_LocationLoggingShowsLocation)
{
    // need support for custom/pattern logging in order to test it
}

TEST_F(LoggerTest, TestDEBUGMacro)
{
    auto sop = setupMacroTest();
    SHARKLOG_DEBUG(Logger::rootLogger(), "test");
    ASSERT_TRUE(testMacro("DEBUG", sop->output_));
}

TEST_F(LoggerTest, TestTRACEMacro)
{
    auto sop = setupMacroTest();
    SHARKLOG_TRACE(Logger::rootLogger(), "test");
    ASSERT_TRUE(testMacro("TRACE", sop->output_));
}

TEST_F(LoggerTest, TestINFOMacro)
{
    auto sop = setupMacroTest();
    SHARKLOG_INFO(Logger::rootLogger(), "test");
    ASSERT_TRUE(testMacro("INFO", sop->output_));
}

TEST_F(LoggerTest, TestWARNMacro)
{
    auto sop = setupMacroTest();
    SHARKLOG_WARN(Logger::rootLogger(), "test");
    ASSERT_TRUE(testMacro("WARN", sop->output_));
}

TEST_F(LoggerTest, TestERRORMacro)
{
    auto sop = setupMacroTest();
    SHARKLOG_ERROR(Logger::rootLogger(), "test");
    ASSERT_TRUE(testMacro("ERROR", sop->output_));
}

TEST_F(LoggerTest, TestFATALMacro)
{
    auto sop = setupMacroTest();
    SHARKLOG_FATAL(Logger::rootLogger(), "test");
    ASSERT_TRUE(testMacro("FATAL", sop->output_));
}

TEST_F(LoggerTest, TestVersion)
{
    auto re = regex("^[0-9]\\.[0-9]{1,2}\\.[0-9]{1,3}");
    ASSERT_TRUE(regex_match(Logger::version().c_str(), re)) << Logger::version().c_str();
}
