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

#include "utilfunctions.h"
#include <sstream>
#include <chrono>
#include <time.h>
#include <cstring>

#if defined(_MSC_VER)
#include <windows.h>
#endif

using namespace sharklog;
using namespace std;
using namespace std::chrono;

std::vector<std::string> sharklog::UtilFunctions::split(const std::string &toSplit, char delim, bool discardEmptyTokens)
{
    std::vector<std::string> split;
    std::stringstream ss;
    ss.str(toSplit);
    std::string item;
    while (getline(ss, item, delim))
    {
        if (item.size() || !discardEmptyTokens)
            split.push_back(item);
    }
    
    return split;
}

std::string UtilFunctions::stripLastToken(const std::string &s, char delim)
{
    auto pos = s.find_last_of(delim);
    if (pos == string::npos)
        return s;
    
    return s.substr(0, pos);
}

UtilFunctions::Time::Time() :
	ms_(0)
{
	getCurrentTime();
}

void UtilFunctions::Time::getCurrentTime()
{
#if defined(_MSC_VER)
	auto tt = time(NULL);
	localtime_r(&tt, &tms_);
	SYSTEMTIME lt;
	GetLocalTime(&lt);
	ms_ = lt.wMilliseconds;
#else
	auto ms = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
	time_t current = duration_cast<seconds>(ms).count();
	localtime_r(&current, &tms_);
	ms_ = ms.count() % 1000;
#endif
}
