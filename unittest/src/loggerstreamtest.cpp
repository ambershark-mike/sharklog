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
#include "location.h"
#include <string>
#include <standardlayout.h>
#include "loggertest.h"
#include <regex>

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
    ls << Location("file", "func", 20);
    ASSERT_STREQ("File: file Function: func Line: 20", ls.location().formattedString().c_str());
}

TEST_F(LoggerStreamTest, StreamedEndFlushesAndClears)
{
    Logger::rootLogger()->setLayout(LayoutPtr(new StandardLayout));
    LoggerStream ls;
    ls << "hello world" << LoggerStream::end;
    ASSERT_TRUE(ls.data().empty());
}

TEST_F(LoggerStreamTest, StreamedEndLogs)
{
    Logger::rootLogger()->setLayout(LayoutPtr(new StandardLayout));
    Logger::rootLogger()->addOutputter(OutputterPtr(new StringOutputter));
    LoggerStream ls;
    ls << "hello world" << LoggerStream::end;
    auto sop = dynamic_cast<StringOutputter *>(Logger::rootLogger()->outputters().front().get());
    auto re = regex("^\\[[0-9]{2}\\/[0-9]{2}\\/[0-9]{4}\\]\\[[0-9]{2}:[0-9]{2}:[0-9]{2}.[0-9]{3}\\]\\[0x[a-z0-9]{12}\\]\\[TRACE\\] hello world\n");
    ASSERT_TRUE(regex_match(sop->output_.c_str(), re)) << sop->output_.c_str();
}

TEST_F(LoggerStreamTest, StreamingAfterEndWorks)
{
    Logger::rootLogger()->setLayout(LayoutPtr(new StandardLayout));
    Logger::rootLogger()->addOutputter(OutputterPtr(new StringOutputter));
    LoggerStream ls;
    ls << "hello world" << LoggerStream::end;
    auto sop = dynamic_cast<StringOutputter *>(Logger::rootLogger()->outputters().front().get());
    auto re = regex("^\\[[0-9]{2}\\/[0-9]{2}\\/[0-9]{4}\\]\\[[0-9]{2}:[0-9]{2}:[0-9]{2}.[0-9]{3}\\]\\[0x[a-z0-9]{12}\\]\\[TRACE\\] hello world\n");
    EXPECT_TRUE(regex_match(sop->output_.c_str(), re)) << sop->output_.c_str();
    
    ls << Level::fatal() << "next one" << LoggerStream::end;
    re = regex("^\\[[0-9]{2}\\/[0-9]{2}\\/[0-9]{4}\\]\\[[0-9]{2}:[0-9]{2}:[0-9]{2}.[0-9]{3}\\]\\[0x[a-z0-9]{12}\\]\\[FATAL\\] next one\n");
    ASSERT_TRUE(regex_match(sop->output_.c_str(), re)) << sop->output_.c_str();
}

TEST_F(LoggerStreamTest, TestEndMacro)
{
    Logger::rootLogger()->setLayout(LayoutPtr(new StandardLayout));
    Logger::rootLogger()->addOutputter(OutputterPtr(new StringOutputter));
    LoggerStream ls;
    ls << "test" << SHARKLOG_END;
    auto sop = dynamic_cast<StringOutputter *>(Logger::rootLogger()->outputters().front().get());
    auto re = regex("^\\[[0-9]{2}\\/[0-9]{2}\\/[0-9]{4}\\]\\[[0-9]{2}:[0-9]{2}:[0-9]{2}.[0-9]{3}\\]\\[0x[a-z0-9]{12}\\]\\[TRACE\\] test\n");
    ASSERT_TRUE(regex_match(sop->output_.c_str(), re)) << sop->output_.c_str();
}

TEST_F(LoggerStreamTest, TestEndMacroAddsLocation)
{
    LoggerStream ls;
    ls << "test" << SHARKLOG_END;
    ASSERT_FALSE(ls.location().empty());
}
