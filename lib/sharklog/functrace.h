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
 * This class allows for backtrace/call stack type logging.  If you instantiate
 * this object at the top of your function it will log an enter into the function,
 * something like `>> void MyFunc()` and then when the function exits the stack
 * will be cleaned up which will cause a log like `<< void MyFunc()`.
 *
 * The enter/exit header can be changed using FuncTrace::setEnterHeader() and
 * FuncTrace::setExitHeader().
 *
 * There are 2 supporting macros to make it easy to use FuncTrace.  These are
 * \ref SHARKLOG_FUNCTRACE and \ref SHARKLOG_FUNCTRACE_ROOT.
 *
 * Using these macros will provide the location automatically for you.  For example:
 * \code
 * void doSomething()
 * {
 *    SHARKLOG_FUNCTRACE_ROOT;
 *
 *    SHARKLOG_TRACE(Logger::rootLogger(), "Hello!");
 * }
 *
 * int foo()
 * {
 *    SHARKLOG_FUNCTRACE_ROOT;
 *
 *    doSomething();
 * }
 *
 * int main()
 * {
 *    foo();
 * }
 * \endcode
 *
 * The above code will log the following to the root logger:
 * ```
 * [...] >> int foo()
 * [...] >> void doSomething()
 * [...] Hello!
 * [...] << void doSomething()
 * [...] << int foo()
 * ```
 *
 * You can specify a logger with the other macro:
 * \code
 * int bar()
 * {
 *    SHARKLOG_FUNCTRACE(Logger::logger("test"));
 * }
 * \endcode
 *
 * Or finally you can use the class directly:
 * \code
 * int fooBar()
 * {
 *    sharklog::FuncTrace ft(Logger::rootLogger(), SHARKLOG_LOCATION);
 * }
 * \endcode
 */
class FuncTrace
{
public:
    /*!
     * \brief Constructor
     *
     * Constructor for FuncTrace.
     *
     * This is the only way to use this object as it is made to be utilized
     * during construct/destruct only.
     *
     * @param logger The logger to use for this message
     * @param loc A Location object for the current location in code
     */
    FuncTrace(LoggerPtr logger, const Location &loc);
    
    /*!
     * \brief Destructor
     *
     * Destructor for FuncTrace.
     *
     * This will log the exit of a function as it is called when the function
     * exits.
     */
    virtual ~FuncTrace();
    
    /*!
     * \brief Sets the log enter header
     *
     * Sets the header that is used to denote entering a function.  The default
     * is ">>".
     *
     * This is global to all FuncTrace objects.
     *
     * You can set the exit header as well.
     *
     * @param hdr the new header to use
     * \sa setExitHeader, enterHeader, exitHeader
     */
    static void setEnterHeader(const std::string &hdr);
    
    /*!
     * \brief Sets the log exit header
     *
     * Sets the header that is used to denote exiting a function.  The default
     * is "<<".
     *
     * This is a global to all FuncTrace objects.
     *
     * You can set the enter header as well.
     *
     * @param hdr the new header to use
     * \sa setEnterHeader, enterHeader, exitHeader
     */
    static void setExitHeader(const std::string &hdr);
    
    /*!
     * \brief Gets the enter header
     *
     * Returns the currently set enter function header.
     *
     * @return the enter header
     * \sa exitHeader, setEnterHeader, setExitHeader
     */
    static std::string enterHeader();
    
    /*!
     * \brief Gets the exit header
     *
     * Returns the currently set exit function header.
     *
     * @return the exit header
     * \sa enterHeader, setEnterHeader, setExitHeader
     */
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

