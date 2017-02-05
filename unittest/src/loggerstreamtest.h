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
// You should have received a copy of the GNU Lesser General Public
// License along with this program.  If not see
// <http://www.gnu.org/licenses>.
//
// This notice must remain in the source code and any derived source.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __loggerstreamtest_H
#define __loggerstreamtest_H

#include <gtest/gtest.h>
#include "logger.h"
#include "loggertest.h"
#include "standardlayout.h"

class LoggerStreamTest : public ::testing::Test
{
protected:
    LoggerStreamTest() { }
    
    void SetUp()
    {
        auto op = std::make_shared<StringOutputter>();
        op->setLayout(std::make_shared<sharklog::StandardLayout>());
        sharklog::Logger::rootLogger()->addOutputter(op);
    }
    
    void TearDown()
    {
        sharklog::Logger::closeRootLogger();
    }
};

#endif // loggerstreamtest_H
