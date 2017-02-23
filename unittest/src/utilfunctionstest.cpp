//
// Created by mike on 9/11/16.
//

#include "utilfunctionstest.h"
#include "utilfunctions.h"

using namespace sharklog;
using namespace std;

UtilFunctionsTest::UtilFunctionsTest()
{
}

UtilFunctionsTest::~UtilFunctionsTest()
{
}

void UtilFunctionsTest::SetUp()
{
}

void UtilFunctionsTest::TearDown()
{
}

TEST_F(UtilFunctionsTest, SplitWorksWithoutEmptyTokens)
{
    auto vec = UtilFunctions::split("com.ambershark.sharklog", '.');
    ASSERT_EQ(3, vec.size());
    ASSERT_STREQ("com", vec.at(0).c_str());
    ASSERT_STREQ("ambershark", vec.at(1).c_str());
    ASSERT_STREQ("sharklog", vec.at(2).c_str());
}

TEST_F(UtilFunctionsTest, SplitDropsEmpties)
{
    auto vec = UtilFunctions::split("com.ambershark..sharklog", '.');
    ASSERT_EQ(3, vec.size());
    ASSERT_STREQ("com", vec.at(0).c_str());
    ASSERT_STREQ("ambershark", vec.at(1).c_str());
    ASSERT_STREQ("sharklog", vec.at(2).c_str());
}

TEST_F(UtilFunctionsTest, SplitKeepsEmpties)
{
    auto vec = UtilFunctions::split("com.ambershark..sharklog", '.', false);
    ASSERT_EQ(4, vec.size());
    ASSERT_STREQ("com", vec.at(0).c_str());
    ASSERT_STREQ("ambershark", vec.at(1).c_str());
    ASSERT_STREQ("", vec.at(2).c_str());
    ASSERT_STREQ("sharklog", vec.at(3).c_str());
}

TEST_F(UtilFunctionsTest, EmptyStringEmptyVector)
{
    auto vec = UtilFunctions::split("", '.');
    ASSERT_EQ(0, vec.size());
}

TEST_F(UtilFunctionsTest, BadDelimIsOneString)
{
    auto vec = UtilFunctions::split("hello", ' ');
    ASSERT_EQ(1, vec.size());
    ASSERT_STREQ("hello", vec.at(0).c_str());
}

TEST_F(UtilFunctionsTest, TestWithSpaceDelim)
{
    auto vec = UtilFunctions::split("hello world", ' ');
    ASSERT_EQ(2, vec.size());
}

TEST_F(UtilFunctionsTest, StripLastWorksWith2)
{
    auto s = UtilFunctions::stripLastToken("com.ambershark", '.');
    ASSERT_STREQ("com", s.c_str());
}

TEST_F(UtilFunctionsTest, StripLastWorksWith3)
{
    auto s = UtilFunctions::stripLastToken("com.ambershark.sharklog", '.');
    ASSERT_STREQ("com.ambershark", s.c_str());
    
    s = UtilFunctions::stripLastToken(s, '.');
    ASSERT_STREQ("com", s.c_str());
}

TEST_F(UtilFunctionsTest, StripLastReturnsEmptyWhenPassedEmpty)
{
    auto s = UtilFunctions::stripLastToken("", '.');
    ASSERT_STREQ("", s.c_str());
}

TEST_F(UtilFunctionsTest, StripLastReturnsStringWhenNoDelim)
{
    auto s = UtilFunctions::stripLastToken("testing 1 2 3", '.');
    ASSERT_STREQ("testing 1 2 3", s.c_str());
}

TEST_F(UtilFunctionsTest, CurrentTimeWorks)
{
	auto curTime = time(NULL);
	tm curTimeTM;
    localtime_r(&curTime, &curTimeTM);

    UtilFunctions::Time testTime;

	char curTimeStr[100], testTimeStr[100];
    const char *format = "%Y-%m-%d %H:%M:%S";
    strftime(curTimeStr, sizeof(curTimeStr), format, &curTimeTM);
    strftime(testTimeStr, sizeof(testTimeStr), format, testTime.tmStruct());

    ASSERT_STREQ(curTimeStr, testTimeStr);
	ASSERT_TRUE(testTime.tmStruct()->tm_year >= (2017 - 1900)) << "Year is: " << testTime.tmStruct()->tm_year; // verify we don't get some 1970 default stamp on both times
}

TEST_F(UtilFunctionsTest, CurrentTimeMSReturnWorks)
{
	UtilFunctions::Time t;
    ASSERT_TRUE(t.ms() >= 0);
    ASSERT_TRUE(t.ms() < 1000);
}
