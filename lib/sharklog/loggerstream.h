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

#ifndef __loggerstream_H
#define __loggerstream_H

#include <sharklog/level.h>
#include <sharklog/logger.h>
#include <sstream>

namespace sharklog
{
    
class Location;
    
/*!
 * \brief Streams for the Logger
 *
 * \todo document this
 */
class LoggerStream
{
public:
    LoggerStream(LoggerPtr lp=Logger::rootLogger(), const Level &lev=Level::trace());
    LoggerStream(const std::string &loggerName, const Level &lev=Level::trace());
    
    LoggerPtr logger() const;
    Level level() const;
    std::string data() const;
    
    void setLevel(const Level &lev);
    void setLogger(LoggerPtr lp);
    
    // stream control/manipulation
    LoggerStream &operator<<(const Level &lev);
    LoggerStream &operator<<(const Location &loc);
    static LoggerStream &end(LoggerStream &s);
    
    // allow casting to the underlying basic_ostream
    operator std::basic_ostream<char>&();
    
    // allow streaming of anything that basic_ostream can handle
    template <class var>
    inline sharklog::LoggerStream &operator<<(const var &val)
    {
        ((std::basic_ostream<char>&) *this) << val;
        return *this;
    }
    
    void end();
    
private:
    // block copies
    LoggerStream(LoggerStream &) { }
    LoggerStream &operator=(LoggerStream &) { return *this; }
    
    LoggerPtr logger_;
    Level level_;
    std::basic_stringstream<char> data_;
};
    
} // sharklog

#endif // loggerstream_H
