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

	std::string formatTime(const std::string &format, tm *ttu=0)
	{
		return Layout::formatTime(format, ttu);
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

TEST(LayoutTest, FormatTimeWithNullTimeGivesCurrentTime)
{
	TestLayout lay;
	const char *format = "%Y-%m-%d %H:%M:%S";
	auto res = lay.formatTime(format);

	// NOTE: this could potentially fail if the second changes between the above func call and this one..
	char curTimeStr[100];
	auto curtime = time(NULL);
	auto curTimeTM = localtime(&curtime);

	strftime(curTimeStr, sizeof(curTimeStr), format, curTimeTM);

	ASSERT_STREQ(curTimeStr, res.c_str()) << "NOTE: this could fail by 1 second potentially expected was: " << res.c_str() << " and actual was: " << curTimeStr;
}

TEST(LayoutTest, FormatTimeWithTimePassedWorks)
{
	TestLayout lay;
	const char *format = "%Y-%m-%d %H:%M:%S";

	/*struct tm my_time = { .tm_year=112, // = year 2012
                          .tm_mon=9,    // = 10th month
                          .tm_mday=9,   // = 9th day
                          .tm_hour=8,   // = 8 hours
                          .tm_min=10,   // = 10 minutes
                          .tm_sec=20    // = 20 secs
	};*/

	struct tm my_time;
	my_time.tm_year = 76;
	my_time.tm_mon = 8;
	my_time.tm_mday = 1;
	my_time.tm_hour = 8;
	my_time.tm_min = 10;
	my_time.tm_sec = 20;

	auto res = lay.formatTime(format, &my_time);
	ASSERT_STREQ("1976-09-01 08:10:20", res.c_str());
}

TEST(LayoutTest, EmptyFormatReturnsEmptyString)
{
	TestLayout lay;
	auto res = lay.formatTime("");
	ASSERT_STREQ("", res.c_str());
}

TEST(LayoutTest, InvalidTimeFormatReturnsProperly)
{
	TestLayout lay;

	// test should just return the invalid string %q instead of trying to format it
	auto res = lay.formatTime("%q");
	ASSERT_STREQ("%q", res.c_str());
}
