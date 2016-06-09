#include "loggertest.h"
#include "logger.h"

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

TEST_F(LoggerTest, random)
{
    Logger l;
    ASSERT_TRUE(l.test());
}
