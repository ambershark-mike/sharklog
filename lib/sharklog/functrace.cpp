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

#include "functrace.h"
#include <sstream>

using namespace sharklog;
using namespace std;

std::string FuncTrace::enterHeader_ = ">>";
std::string FuncTrace::exitHeader_ = "<<";

FuncTrace::FuncTrace(LoggerPtr logger, const Location &loc)
    : loc_(loc)
    , logger_(logger)
{
    stringstream ss;
    ss << enterHeader() << " " << loc.function();
    logger->log(Level::functrace(), ss.str());
}

FuncTrace::~FuncTrace()
{
    stringstream ss;
    ss << exitHeader() << " " << loc_.function();
    logger_->log(Level::functrace(), ss.str());
}

std::string FuncTrace::enterHeader()
{
    return enterHeader_;
}

std::string FuncTrace::exitHeader()
{
    return exitHeader_;
}

void FuncTrace::setEnterHeader(const std::string &hdr)
{
    enterHeader_ = hdr;
}

void FuncTrace::setExitHeader(const std::string &hdr)
{
    exitHeader_ = hdr;
}
