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
    
    LoggerStream &operator<<(const Level &lev);
    LoggerStream &operator<<(const Location &loc);
};
    
} // sharklog

#endif // loggerstream_H
