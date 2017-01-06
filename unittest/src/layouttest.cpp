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
#include "layout.h"

using namespace sharklog;

class TestLayout : public Layout
{
public:
    void formatMessage(std::string &result, const Level &level, const std::string &loggerName, const std::string &logMessage) final
    {
    }
};

TEST(LayoutTest, BaseContentTypeIsTextPlain)
{
    TestLayout lay;
    ASSERT_STREQ("text/plain", lay.contentType().c_str());
}

TEST(LayoutTest, BaseAppendHeaderDoesNothing)
{
    TestLayout lay;
    std::string res;
    lay.appendHeader(res);
    ASSERT_TRUE(res.empty());
}

TEST(LayoutTest, BaseAppendFooterDoesNothing)
{
    TestLayout lay;
    std::string res;
    lay.appendFooter(res);
    ASSERT_TRUE(res.empty());
}
