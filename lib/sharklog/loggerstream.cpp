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

#include "loggerstream.h"

using namespace sharklog;

LoggerStream::LoggerStream(LoggerPtr lp, const Level &lev)
{
    setLevel(lev);
    setLogger(lp);
}

LoggerStream::LoggerStream(const std::string &loggerName, const Level &lev)
{
    setLevel(lev);
    setLogger(Logger::logger(loggerName));
}

LoggerStream &LoggerStream::operator<<(const Level &lev)
{
    setLevel(lev);
    return *this;
}

LoggerStream &LoggerStream::operator<<(const Location &loc)
{
    loc_ = loc;
    return *this;
}

void LoggerStream::end()
{
    // log the message
    logger()->log(level(), data_.str(), loc_);
    
    // clear the stream
    std::basic_string<char> emp;
    data_.str(emp);
}

LoggerStream &LoggerStream::end(LoggerStream &s)
{
    s.end();
    return s;
}

LoggerPtr LoggerStream::logger() const
{
    return logger_;
}

Level LoggerStream::level() const
{
    return level_;
}

void LoggerStream::setLevel(const Level &lev)
{
    level_ = lev;
}

void LoggerStream::setLogger(LoggerPtr lp)
{
    logger_ = lp;
}

std::string LoggerStream::data() const
{
    return data_.str();
}

Location LoggerStream::location() const
{
    return loc_;
}

LoggerStream &LoggerStream::operator<<(LoggerFuncPtr pf)
{
    return (*pf)(*this);
}

LoggerStream::operator std::basic_ostream<char> &()
{
    return data_;
}
