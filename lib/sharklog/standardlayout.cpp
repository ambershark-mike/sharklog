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

#include "standardlayout.h"
#include "level.h"
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
    ss << "[";
    if (loggerName.empty())
        ss << "UNNAMED";
    else
        ss << loggerName;
    ss << "]";
    
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
    
    time_t current = system_clock::to_time_t(system_clock::now());
    tm *tmt = localtime(&current);
    
    ss << "[" << put_time(tmt, "%m/%d/%Y") << "]";
    
    s.append(ss.str());
}

void StandardLayout::setupTime(std::string &s)
{
    stringstream ss;
    auto ms = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
    time_t current = duration_cast<seconds>(ms).count();
    auto msec = ms.count() % 1000;
    tm *tmt = localtime(&current);
    
    ss << "[" << put_time(tmt, "%H:%M:%S") << "." << setfill('0') << setw(3) << msec << "]";
    s.append(ss.str());
}

void StandardLayout::setupThread(std::string &s)
{
    stringstream ss;
    ss << "[0x" << hex << this_thread::get_id() << "]";
    s.append(ss.str());
}
