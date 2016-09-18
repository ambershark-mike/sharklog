#ifndef __loggertest_H
#define __loggertest_H

#include <gtest/gtest.h>
//#include "Logger.h"

class LoggerTest : public ::testing::Test
{
protected:
    LoggerTest();
    virtual ~LoggerTest();

    virtual void SetUp();
    virtual void TearDown();
};

#endif // loggertest_H
