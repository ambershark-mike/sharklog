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
#include <sharklog/location.h>
#include <sstream>

/*!
 * \file loggerstream.h
 */

namespace sharklog
{
    
class LoggerStream;
using LoggerFuncPtr = LoggerStream &(*)(LoggerStream&);
    
/*!
 * \brief Streams for the Logger
 *
 * \todo document this
 */
class LoggerStream
{
public:
    /*!
     * \brief Constructor
     *
     * Use this to create a LoggerStream.
     *
     * It takes a \ref LoggerPtr and a \ref Level.  It defaults to the root logger
     * at a trace level.
     *
     * Example:
     * \code
     * LoggerStream(Logger::logger("test"), Level::info()) << "this is a test log to the test logger at info level" << SHARKLOG_END;
     * \endcode
     *
     * @param lp pointer to a logger
     * @param lev level for logging
     */
    LoggerStream(LoggerPtr lp=Logger::rootLogger(), const Level &lev=Level::trace());
    
    /*!
     * \brief Constructor
     *
     * Takes a name for a logger, same as using Logger::logger(loggerName).  Also takes
     * a level.
     *
     * @param loggerName name of a logger
     * @param lev level for logging
     */
    LoggerStream(const std::string &loggerName, const Level &lev=Level::trace());
    
    LoggerPtr logger() const;
    Level level() const;
    std::string data() const;
    Location location() const;
    
    void setLevel(const Level &lev);
    void setLogger(LoggerPtr lp);
    
    // stream control/manipulation
    LoggerStream &operator<<(const Level &lev);
    LoggerStream &operator<<(const Location &loc);
    LoggerStream &operator<<(LoggerFuncPtr pf);
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
    
    Location loc_;
    LoggerPtr logger_;
    Level level_;
    std::basic_stringstream<char> data_;
};

/*!
 * \brief End log macro
 *
 * Use this macro to easily end a log message that is being written
 * via a \ref LoggerStream.
 *
 * It also adds location information to the log message.
 *
 * \code
 * LoggerStream ls;
 * ls << "testing" << SHARKLOG_END;
 * \endcode
 */
#define SHARKLOG_END SHARKLOG_LOCATION << sharklog::LoggerStream::end

} // sharklog

#endif // loggerstream_H
