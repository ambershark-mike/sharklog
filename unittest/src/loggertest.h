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

#ifndef __loggertest_H
#define __loggertest_H

#include <gtest/gtest.h>
#include <sharklog/outputter.h>
#include <string>

class StringOutputter : public sharklog::Outputter
{
public:
    bool open() final
    {
        return true;
    }
    
    void writeLog(const std::string &logMessage) final
    {
        output_ = logMessage;
    }
    
    void close() final { }
    
    bool isOpen() const final { return true; }
    
    std::string output_;
};

class LoggerTest : public ::testing::Test
{
protected:
    LoggerTest();
    virtual ~LoggerTest();

    virtual void SetUp();
    virtual void TearDown();
    
    StringOutputter *setupMacroTest();
    bool testMacro(const std::string &type, const std::string &test);
};

#endif // loggertest_H
