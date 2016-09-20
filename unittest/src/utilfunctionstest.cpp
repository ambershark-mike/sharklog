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
