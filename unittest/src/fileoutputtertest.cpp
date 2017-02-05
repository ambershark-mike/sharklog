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

#include <regex>
#include "fileoutputtertest.h"
#include "fileoutputter.h"
#include "logger.h"

using namespace sharklog;
using namespace std;

unsigned int FileOutputterTest::getFileSize(const std::string &filename)
{
	ifstream f(filename, ios::binary);
	f.seekg(0, ios::end);
	auto end = f.tellg();
	f.close();

	return end;
}

void FileOutputterTest::writeTest()
{
	FileOutputter fo(filename_);
    fo.setLayout(make_shared<FOTestLayout>());
	EXPECT_TRUE(fo.open());
    EXPECT_TRUE(fo.isValid());
	fo.writeLog(Level::trace(), "", "test", Location());
	fo.close();
}

TEST_F(FileOutputterTest, SetAppendWorks)
{
    FileOutputter fo;
	fo.setAppend(false);
    EXPECT_FALSE(fo.append());
    fo.setAppend(true);
    ASSERT_TRUE(fo.append());
}

TEST_F(FileOutputterTest, ConstructorSetsName)
{
    FileOutputter fo("test");
    ASSERT_STREQ("test", fo.filename().c_str());
}

TEST_F(FileOutputterTest, SetNameWorks)
{
    FileOutputter fo;
    fo.setFilename("test");
    ASSERT_STREQ("test", fo.filename().c_str());
}

TEST_F(FileOutputterTest, OpenWorks)
{
	FileOutputter fo(filename_);
	ASSERT_TRUE(fo.open());
	ASSERT_TRUE(fo.isOpen());
}

TEST_F(FileOutputterTest, CloseWorks)
{
	FileOutputter fo(filename_);
	EXPECT_TRUE(fo.open());
	fo.close();
	ASSERT_FALSE(fo.isOpen());
}

TEST_F(FileOutputterTest, DefaultAppendIsFalse)
{
	FileOutputter fo;
	ASSERT_FALSE(fo.append());
}

TEST_F(FileOutputterTest, AppendModeWorks)
{
	writeTest();

	auto startSize = getFileSize(filename_);
	EXPECT_GT(startSize, 0);

	FileOutputter fo(filename_);
    fo.setLayout(make_shared<FOTestLayout>());
	fo.setAppend(true);
	EXPECT_TRUE(fo.open());
    EXPECT_TRUE(fo.isValid());
	fo.writeLog(Level::trace(), "", "x", Location());
	fo.close();

	ASSERT_EQ(getFileSize(filename_), startSize+1);
}

TEST_F(FileOutputterTest, NonAppendTruncates)
{
	writeTest();

	EXPECT_GT(getFileSize(filename_), 0);

	FileOutputter fo(filename_);
	EXPECT_TRUE(fo.open());
	fo.close();

	EXPECT_EQ(0, getFileSize(filename_));
}

TEST_F(FileOutputterTest, SetFileNameClosesFile)
{
	FileOutputter fo(filename_);
	EXPECT_TRUE(fo.open());
	fo.setFilename("xyz");
	ASSERT_FALSE(fo.isOpen());
}

TEST_F(FileOutputterTest, WriteLogWorks)
{
	FileOutputter fo(filename_);
    fo.setLayout(make_shared<FOTestLayout>());
	EXPECT_TRUE(fo.open());
	fo.writeLog(Level::trace(), "", "test\n", Location());
	fo.close();

	string line;
	ifstream file(filename_);
	EXPECT_TRUE(file.is_open());
	getline(file, line);
    EXPECT_FALSE(line.empty());
    
    //auto re = regex("^\\[[0-9]{2}\\/[0-9]{2}\\/[0-9]{4}\\]\\[[0-9]{2}:[0-9]{2}:[0-9]{2}.[0-9]{3}\\]\\[0x[a-z0-9]{12}\\]\\[TRACE\\] test\n");
    //ASSERT_TRUE(regex_match(line.c_str(), re)) << line.c_str();
    
	ASSERT_STREQ("test", line.c_str());
	file.close();
}
