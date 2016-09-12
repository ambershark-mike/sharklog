#include "loggertest.h"
#include "Logger.h"

using namespace sharklog;

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

TEST_F(LoggerTest, GetANamedLoggerWorks)
{
    ASSERT_TRUE((bool)Logger::logger("test"));
}

TEST_F(LoggerTest, NamedLoggerNameMatches)
{
    ASSERT_STREQ(Logger::logger("test")->name().c_str(), "test");
}

TEST_F(LoggerTest, SimpleNameLoggerParentIsRoot)
{
    ASSERT_TRUE(Logger::logger("test")->parent() == Logger::rootLogger());
}

TEST_F(LoggerTest, RootHasNoParent)
{
    ASSERT_FALSE((bool)Logger::rootLogger()->parent());
}

TEST_F(LoggerTest, GetNamedLoggerThatExists)
{
    EXPECT_TRUE((bool)Logger::logger("existloggertest"));
    ASSERT_TRUE((bool)Logger::logger("existloggertest"));
}

TEST_F(LoggerTest, EmptyNameLoggerGetsRoot)
{
    ASSERT_TRUE(Logger::logger("")->isRoot());
}
