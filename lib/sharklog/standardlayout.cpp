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

#include "standardlayout.h"
#include "level.h"
#include "utilfunctions.h"
#include <sstream>
#include <chrono>
#include <thread>
#include <iomanip>

using namespace sharklog;
using namespace std;
using namespace std::chrono;

StandardLayout::~StandardLayout()
{
}

void StandardLayout::formatMessage(std::string &result, const Level &level, const std::string &loggerName,
                                   const std::string &logMessage)
{
    stringstream ss;
    
    // add name
    if (!loggerName.empty())
		ss << "[" << loggerName << "]";
    
    // add level
    ss << "[" << level.name() << "]";
    
    // add message
    ss << " " << logMessage << endl;
    
    result.append(ss.str());
}

void StandardLayout::appendHeader(std::string &result)
{
    setupDate(result);
    setupTime(result);
    setupThread(result);
}

void StandardLayout::appendFooter(std::string &result)
{
}

void StandardLayout::setupDate(std::string &s)
{
    stringstream ss;
    UtilFunctions::Time t;

    ss << "[" << formatTime("%m/%d/%Y", t.tmStruct()) << "]";
    
    s.append(ss.str());
}

void StandardLayout::setupTime(std::string &s)
{
    stringstream ss;

	UtilFunctions::Time t;

    ss << "[" << formatTime("%H:%M:%S", t.tmStruct()) << "." << setfill('0') << setw(3) << t.ms() << "]";
    s.append(ss.str());
}

void StandardLayout::setupThread(std::string &s)
{
    stringstream ss;
    ss << "[0x" << hex << this_thread::get_id() << "]";
    s.append(ss.str());
}
