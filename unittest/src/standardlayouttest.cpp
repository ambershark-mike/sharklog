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

#include "standardlayouttest.h"
#include "standardlayout.h"
#include "level.h"
#include <regex>

using namespace sharklog;
using namespace std;

TEST_F(StandardLayoutTest, AppendHeaderWorks)
{
    StandardLayout layout;
    string s;
    layout.appendHeader(s);
    auto re = regex("^\\[[0-9]{2}\\/[0-9]{2}\\/[0-9]{4}\\]\\[[0-9]{2}:[0-9]{2}:[0-9]{2}.[0-9]{3}\\]\\[0x[a-z0-9]{12}\\]");
    ASSERT_TRUE(regex_match(s.c_str(), re)) << s.c_str();
}

TEST_F(StandardLayoutTest, AppendFooterIsBlank)
{
    StandardLayout lo;
    string s;
    lo.appendFooter(s);
    ASSERT_TRUE(s.empty());
}

TEST_F(StandardLayoutTest, FormatMessageWorks)
{
    StandardLayout lo;
    string s;
    lo.formatMessage(s, Level::fatal(), "test", "this is a message  123!");
    auto re = regex("^\\[test\\]\\[(?:TRACE|DEBUG|FATAL|INFO|ERROR|WARN|FUNC)\\] .*\n");
    ASSERT_TRUE(regex_match(s.c_str(), re)) << s.c_str();
}

TEST_F(StandardLayoutTest, BlankMessageWorks)
{
    StandardLayout lo;
    string s;
    lo.formatMessage(s, Level::debug(), "test", "");
    auto re = regex("^\\[test\\]\\[(?:TRACE|DEBUG|FATAL|INFO|ERROR|WARN|FUNC)\\] \n");
    ASSERT_TRUE(regex_match(s.c_str(), re)) << s.c_str();
}

TEST_F(StandardLayoutTest, BlankNameWorks)
{
    StandardLayout lo;
    string s;
    lo.formatMessage(s, Level::info(), "", "message");
    auto re = regex("^\\[UNNAMED\\]\\[(?:TRACE|DEBUG|FATAL|INFO|ERROR|WARN|FUNC)\\] .*\n");
    ASSERT_TRUE(regex_match(s.c_str(), re)) << s.c_str();
}

TEST_F(StandardLayoutTest, InvalidLevelWorks)
{
    StandardLayout lo;
    string s;
    lo.formatMessage(s, Level(), "", "message");
    auto re = regex("^\\[UNNAMED\\]\\[NONE\\] .*\n");
    ASSERT_TRUE(regex_match(s.c_str(), re)) << s.c_str();
}
