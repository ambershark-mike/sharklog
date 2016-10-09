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

#include "fileoutputtertest.h"
#include "fileoutputter.h"

using namespace sharklog;

TEST(FileOutputterTest, SetAppendWorks)
{
    FileOutputter fo;
    EXPECT_FALSE(fo.append());
    fo.setAppend(true);
    ASSERT_TRUE(fo.append());
}

TEST(FileOutputterTest, ConstructorSetsName)
{
    FileOutputter fo("test");
    ASSERT_STREQ("test", fo.filename().c_str());
}

TEST(FileOutputterTest, SetNameWorks)
{
    FileOutputter fo;
    fo.setFilename("test");
    ASSERT_STREQ("test", fo.filename().c_str());
}

TEST(FileOutputterTest, DISABLED_SetFileNameClosesFile)
{
}

TEST(FileOutputterTest, DISABLED_DestructorClosesFile)
{
}
