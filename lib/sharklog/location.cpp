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

#include "location.h"
#include <sstream>

using namespace sharklog;
using namespace std;

Location::Location(const std::string &file, const std::string &function, int line)
    : file_(file)
    , function_(function)
    , line_(line)
{
}

bool Location::empty() const
{
    return !(line_ && !function_.empty() && !file_.empty());
}

std::string Location::formattedString() const
{
    stringstream ss;
    ss << "File: " << file() << " Function: " << function() << " Line: " << line();
    return ss.str();
}
