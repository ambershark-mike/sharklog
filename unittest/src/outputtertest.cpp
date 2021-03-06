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

#include <gtest/gtest.h>
#include "outputter.h"
#include "standardlayout.h"

using namespace sharklog;

class TestOutputter : public Outputter
{
public:
    bool open() final { return false; }
    void close() final { }
    void writeLog(const Level &lev, const std::string &loggerName, const std::string &logMessage, const Location &loc) final { }
};

TEST(OutputterTest, OutputterIsClosed)
{
    TestOutputter t;
    ASSERT_FALSE(t.isOpen());
}

TEST(OutputterTest, DefaultLayoutIsEmpty)
{
	TestOutputter t;
	ASSERT_TRUE(t.layout() == nullptr);
}

TEST(OutputterTest, LayoutReturnsLayout)
{
	TestOutputter t;
    auto lo = std::make_shared<StandardLayout>();
	t.setLayout(lo);
	ASSERT_TRUE(t.layout().get() == lo.get());
}

TEST(OutputterTest, IsValidFailsWithNoLayout)
{
	TestOutputter t;
	ASSERT_FALSE(t.isValid());
}

TEST(OutputterTest, IsValidWorksWithLayout)
{
	TestOutputter t;
	t.setLayout(std::make_shared<StandardLayout>());
	ASSERT_TRUE(t.isValid());
}
