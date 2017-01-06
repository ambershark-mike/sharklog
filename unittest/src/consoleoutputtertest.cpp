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

#include "consoleoutputtertest.h"
#include "consoleoutputter.h"

using namespace sharklog;

TEST_F(ConsoleOutputterTest, OpenIsTrue)
{
    ConsoleOutputter co;
    ASSERT_TRUE(co.open());
}

TEST_F(ConsoleOutputterTest, IsOpen)
{
    ConsoleOutputter co;
    ASSERT_TRUE(co.isOpen());
}

TEST_F(ConsoleOutputterTest, SetUseStdOutWorks)
{
    ConsoleOutputter co;
    EXPECT_TRUE(co.useStdOut());
    co.setUseStdOut(false);
    ASSERT_FALSE(co.useStdOut());
}

TEST_F(ConsoleOutputterTest, SetUseStdErrWorks)
{
    ConsoleOutputter co;
    EXPECT_FALSE(co.useStdErr());
    co.setUseStdErr(true);
    ASSERT_TRUE(co.useStdErr());
}
