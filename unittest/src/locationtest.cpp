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
// You sould have received a copy of the GNU Lesser General Public
// License along with this program.  If not see
// <http://www.gnu.org/licenses>.
//
// This notice must remain in the source code and any derived source.
//
////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>
#include "location.h"
#include <regex>

using namespace sharklog;
using namespace std;

TEST(LocationTest, ConstructorDefaultMakesEmpty)
{
    Location loc;
    ASSERT_TRUE(loc.file().empty());
    ASSERT_TRUE(loc.function().empty());
    ASSERT_FALSE(loc.line());
}

TEST(LocationTest, FilledConstructorWorks)
{
    Location loc("file", "function", 10);
    ASSERT_STREQ("file", loc.file().c_str());
    ASSERT_STREQ("function", loc.function().c_str());
    ASSERT_EQ(10, loc.line());
}

TEST(LocationTest, TestLocationCreationMacro)
{
    auto loc = SHARKLOG_LOCATION;
    
    auto re = regex("^[a-z]* [a-z].*\\(.*\\)");
    ASSERT_TRUE(regex_match(loc.function().c_str(), re)) << loc.function().c_str();
    
    re = regex("^.*(locationtest.cpp)");
    ASSERT_TRUE(regex_match(loc.file().c_str(), re)) << loc.file().c_str();
    
    ASSERT_GT(loc.line(), 0);
}

TEST(LocationTest, TestEmpty)
{
    ASSERT_FALSE(SHARKLOG_LOCATION.empty());
    ASSERT_TRUE(Location().empty());
}

TEST(LocationTest, FormattedStringWorks)
{
    Location loc("file", "func", 10);
    ASSERT_STREQ("File: file Function: func Line: 10", loc.formattedString().c_str());
}