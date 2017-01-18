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
 * This class allows streaming of log messages.  It is not as fast as logging
 * directly via the \ref SHARKLOG_TRACE type macros, but it is a lot more
 * convenient and powerful.
 *
 * Here are a few examples:
 * \code
 * // simple log at trace level to root
 * LoggerStream() << "my number is " << 10 << SHARKLOG_END;
 *
 * // log to a named logger at info level
 * LoggerStream(Logger::logger("test"), Level::info()) << "test info message" << SHARKLOG_END;
 *
 * // log to root logger at fatal level
 * LoggerStream() << Level::fatal() << "this is a fatal message" << SHARKLOG_END;
 *
 * // Create a persistent stream
 * LoggerStream ls;
 * ls << "log at root/trace" << SHARKLOG_END;
 * ls << Level::info() << "Here is an info message" << SHARKLOG_END;
 * ls.setLevel(Level::warn());
 * ls << "This is a warning";
 * ls.end();
 * \endcode
 *
 * \note A stream will never flush out to the logger if you don't call \ref end() or \ref SHARKLOG_END.
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
    
    /*!
     * \brief Gets logger used by the stream
     *
     * Returns the logger that is currently being used by this stream.
     *
     * @return The LoggerPtr for the logger
     */
    LoggerPtr logger() const;
    
    /*!
     * \brief Level of the stream
     *
     * Returns the level that is set for this stream.  You can change the level with
     * \ref setLevel(), or by streaming a \ref Level into the stream.
     *
     * Level is set in the constructor initially.
     *
     * @return Level of the stream
     */
    Level level() const;
    
    /*!
     * \brief Current stream data
     *
     * Gets the data that is in the stream.
     *
     * @return String containing the stream data
     */
    std::string data() const;
    
    /*!
     * \brief Location of the logged message
     *
     * Gets the set \ref Location for this log message.
     *
     * @return The code \ref Location
     */
    Location location() const;
    
    /*!
     * \brief Set the \ref Level
     *
     * Sets the level of the log stream.
     *
     * @param lev The level you want for the log
     */
    void setLevel(const Level &lev);
    
    /*!
     * \brief Set the logger
     *
     * Sets the logger you want this stream to log to when it is endede with SHARKLOG_END.
     *
     * @param lp The logger to use
     */
    void setLogger(LoggerPtr lp);
    
    /*!
     * \brief Operator for Level
     *
     * You can change the level by streaming a level or by calling \ref setLevel.  This
     * is the streaming one.
     *
     * @param lev Level to set
     * @return Reference to the stream
     */
    LoggerStream &operator<<(const Level &lev);
    
    /*!
     * \brief Operator for Location
     *
     * You can add the location by streaming it in.  The \ref SHARKLOG_END macro will
     * automatically stream in the \ref Location for you.
     *
     * @param loc The \ref Location
     * @return Reference to the stream
     */
    LoggerStream &operator<<(const Location &loc);
    
    /*!
     * \brief Function Stream
     *
     * This allows passing in the end() function to the stream.  This is done typically
     * with \ref SHARKLOG_END.
     *
     * @param pf pointer to the function to stream
     * @return Reference to the stream
     */
    LoggerStream &operator<<(LoggerFuncPtr pf);
    
    /*!
     * \brief Tells stream to end
     *
     * This function when passed in to the stream will tell it to flush the log and reset
     * the stream.  This will log the message to \ref logger() and then clear the stream
     * \ref data().
     *
     * \note Normally just use the \ref SHARKLOG_END macro for ending a stream.
     *
     * @param s The LoggerStream to end
     * @return Reference to the stream
     */
    static LoggerStream &end(LoggerStream &s);
    
    /*!
     * \brief Cast to ostream
     *
     * Casts to the underlying std::basic_ostream.
     *
     * @return The underlying data stream
     */
    operator std::basic_ostream<char>&();
    
    /*!
     * \brief Allows streaming to basic_ostream
     *
     * This template class allows streaming of stuff that std::basic_ostream would
     * normally handle.  This makes it so we don't have to handle all the stuff they
     * already handle.
     *
     * This allows things like:
     * \code
     * LoggerStream() << "an int " << 10 << SHARKLOG_END;
     * \endcode
     *
     * @param val The variable to log
     * @return Reference to the stream
     */
    template <class var>
    inline sharklog::LoggerStream &operator<<(const var &val)
    {
        ((std::basic_ostream<char>&) *this) << val;
        return *this;
    }
    
    /*!
     * \brief Ends the stream
     *
     * This function flushes and resets the stream.  It is best to just use \ref SHARKLOG_END
     * but you can call this directly.
     *
     * \sa SHARKLOG_END, end(LoggerStream &)
     */
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
