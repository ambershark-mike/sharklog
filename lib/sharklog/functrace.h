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

#ifndef __functrace_H
#define __functrace_H

#include <sharklog/logger.h>
#include <sharklog/location.h>

/*!
 * \file functrace.h
 */

namespace sharklog
{
    
class Location;
    
/*!
 * \brief Function trace
 *
 * \todo document this
 */
class FuncTrace
{
public:
    FuncTrace(LoggerPtr logger, const Location &loc);
    virtual ~FuncTrace();
    
    static void setEnterHeader(const std::string &hdr);
    static void setExitHeader(const std::string &hdr);
    
    static std::string enterHeader();
    static std::string exitHeader();
    
private:
    static std::string enterHeader_;
    static std::string exitHeader_;
    Location loc_;
    LoggerPtr logger_;
};

/*!
 * \brief FuncTrace macro
 *
 * Use this macro to easily add a \ref FuncTrace to a function.
 *
 * \code
 * void myFunc()
 * {
 *    SHARKLOG_FUNCTRACE(Logger::logger("test"));
 * }
 * \endcode
 */
#define SHARKLOG_FUNCTRACE(logger) FuncTrace func_trace_(logger, SHARKLOG_LOCATION)

/*!
 * \brief FuncTrace Root Logger macro
 *
 * Use this macro to easily add a \ref FuncTrace using the root logger
 * to a function.
 *
 * \code
 * void myFunc()
 * {
 *    SHARKLOG_FUNCTRACE_ROOT;
 * }
 * \endcode
 */
#define SHARKLOG_FUNCTRACE_ROOT FuncTrace func_trace_(sharklog::Logger::rootLogger(), SHARKLOG_LOCATION)
    
} // sharklog

#endif // functrace_H

