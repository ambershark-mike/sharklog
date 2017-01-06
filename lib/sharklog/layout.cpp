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

#include "layout.h"
#include <time.h>
#include <chrono>
#include <iomanip>

using namespace sharklog;
using namespace std;
using namespace std::chrono;

std::string Layout::contentType() const
{
    return std::string("text/plain");
}

void Layout::appendHeader(std::string &result)
{
}

void Layout::appendFooter(std::string &result)
{
}

Layout::~Layout()
{
}

std::string Layout::formatTime(const std::string &format, tm *timeToUse)
{
	/*tm *tmt = timeToUse;
	if (!tmt)
	{
		auto ms = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
		time_t current = duration_cast<seconds>(ms).count();
		tmt = localtime(&current);
	}*/
    
}
