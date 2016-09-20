
#ifndef PROJECT_UTILFUNCTIONSTEST_H
#define PROJECT_UTILFUNCTIONSTEST_H

#include <gtest/gtest.h>

class UtilFunctionsTest : public ::testing::Test
{
protected:
    UtilFunctionsTest();
    virtual ~UtilFunctionsTest();
    
    virtual void SetUp();
    virtual void TearDown();
};

#endif //PROJECT_UTILFUNCTIONSTEST_H
