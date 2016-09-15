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
    ASSERT_STREQ("com.", log->baseName().c_str());
}

TEST_F(LoggerTest, BaseIsOkWithOnlyAPeriodInName)
{
    auto log = Logger::logger(".");
    ASSERT_STREQ(".", log->name().c_str());
    ASSERT_STREQ(".", log->baseName().c_str());
}

TEST_F(LoggerTest, BaseNameIsOkWithMultipleDots)
{
    auto log = Logger::logger("..");
    ASSERT_STREQ("..", log->baseName().c_str());
    
    log = Logger::logger("...");
    ASSERT_STREQ("...", log->baseName().c_str());
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

TEST_F(LoggerTest, GetNamedLoggerThatExists)
{
    EXPECT_TRUE((bool)Logger::logger("existloggertest"));
    ASSERT_TRUE((bool)Logger::logger("existloggertest"));
}
