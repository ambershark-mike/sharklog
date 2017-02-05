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

#include "fileoutputter.h"

using namespace sharklog;
using namespace std;

std::recursive_mutex FileOutputter::mutex_;

FileOutputter::FileOutputter(const std::string &filename)
{
    setFilename(filename);
    setAppend(false);
}

FileOutputter::~FileOutputter()
{
	close();
}

bool FileOutputter::open()
{
    lock_guard<recursive_mutex> lock(mutex_);

	// close file if it's already open
	close();

	// open file
	if (append_)
		file_.open(filename_, std::ofstream::out | std::ofstream::app);
	else
		file_.open(filename_, std::ofstream::out | std::ofstream::trunc);

    return file_.is_open();
}

void FileOutputter::writeLog(const Level &lev, const std::string &loggerName, const std::string &logMessage, const Location &loc)
{
	if (!isOpen())
		return;

    lock_guard<recursive_mutex> lock(mutex_);

	file_ << logMessage;
}

void FileOutputter::close()
{
    lock_guard<recursive_mutex> lock(mutex_);

	if (file_.is_open())
		file_.close();
}

bool FileOutputter::isOpen() const
{
	return file_.is_open();
}

void FileOutputter::setFilename(const std::string &filename)
{
    lock_guard<recursive_mutex> lock(mutex_);

	close();
    filename_ = filename;
}

std::string FileOutputter::filename() const
{
    return filename_;
}

void FileOutputter::setAppend(bool append)
{
    lock_guard<recursive_mutex> lock(mutex_);
    append_ = append;
}

bool FileOutputter::append() const
{
    return append_;
}
