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

#ifndef __level_H
#define __level_H

#include <string>

namespace sharklog
{
    
/*!
 * @brief Logger level
 * 
 * Represents all logger levels.  Levels determine what should be 
 * logged.  It can be changed to allow more detail i.e. INFO or 
 * less i.e. WARN. 
 *  
 * This class is used to represent logger levels all throughout the 
 * library. 
 *  
 * Typically when a logger level is set it includes all levels below 
 * that level as well.  So a level of WARN would include all other 
 * levels below it, i.e. ERROR and FATAL.
 *  
 * Here is a table explaining each level. 
 *  
 * | Level | Description | 
 * | ----- | ----------- | 
 * | NONE | Indicates no level.  This is set by default on new loggers and in some other situations. |
 * | FATAL | A fatal error.  This is used for non-recoverable system breaking errors. | 
 * | ERROR | An error.  This is used for normal errors but normally things that don't break the application. Basically recoverable errors. | 
 * | WARN | Warning level.  This is used for warnings.  Things that are typically not an error but should be looked into. | 
 * | INFO | Information level.  Used to convey information about the application and what it is doing. | 
 * | TRACE | Trace level.  Used to give some information about what the app is doing that is debug related but not quite as detailed as full debug info. | 
 * | DEBUG | Debug level.  This is used to get all the information about the program.  Typically in most applications utilizing a logger, debug outputs a lot of information and files can grow quite large quickly. | 
 * | FUNCTRACE | Function tracing level.  This is used like a call stack.  The logger will log function entry and exits using this special level.  You should not really use it in your own logging unless you are doing a function tracing custom class or something. | 
 * | ALL | A catch-all level.  This one will guarantee that everything is logged.  Typically not set as most would prefer to use the specific levels. | 
 *  
 * Levels have an integer representation underneath called \ref LogLevel.  This should not 
 * be used outside the application as the related enum could change in the future. 
 * So do not store levels in your settings based on this integer, but instead use the string 
 * values. 
 *  
 * Levels can be created in a number of ways.  The most common will be by using the static 
 * functions.  I.e. 
 *  
 * \code 
 * auto lev = Level::warn()
 * \endcode 
 * That would return a Level object with the set level of WARN. 
 *  
 * Another way is to use the underlying integer from the enum.  In this case you would 
 * construct it like so: 
 *  
 * \code 
 * Level lev(LogLevel::WARN); 
 * \endcode 
 *  
 *  
 * You can also set it based on the name of a level, i.e. 
 * \code 
 * Level lev("warn"); 
 * // or 
 * auto lev = Level::name("warn"); 
 * \endcode 
 *  
 * \note using the name is case insensitive.   So WARN is the same as warn. 
 *  
 * You can test a Level with standard operators, like == or <=.  You can 
 * also use the 'has' functions, i.e. hasError(). 
 *  
 */
class Level
{
public:
	/*!
	 * The underlying level enumator for the \ref Level class.
	 */
    enum LogLevel
    {
        NONE //!< not really a level, more of a lack of one, all levels include this though
        , FATAL //!< Fatal errors
        , ERROR //!< Regular errors
        , WARN //!< Warnings
        , INFO //!< Information
        , TRACE //!< Trace information
        , DEBUG //!< Debug information
        , FUNCTRACE //!< Used internally for Function callback stack tracing
        , ALL //!< this will always be at the end so it includes everything below it
    };
    
	/*!
	 * \brief Default constructor
	 *  
	 * Can be constructed with a \ref LogLevel enum value.  Note these values are 
	 * subject to changed on any release of the library if new levels are introduced. 
	 *  
	 * \param lev An \ref LogLevel enumerated value
	 */
    Level(LogLevel lev = NONE);
    
	//! Creates a fatal Level
    static Level fatal();

	//! Creates an error level
    static Level error();

	//! Creates a warn level
    static Level warn();

	//! Creates an info level
    static Level info();

	//! Creates a trace level
    static Level trace();

	//! Creates a debug level
    static Level debug();

	//! Creates a function trace level
    static Level functrace();

	//! Creates an level that covers everything
    static Level all();
    
	/*!
	 * \brief Gets the level name 
	 *  
	 * Returns a string representation of the level. 
	 *  
	 * This can be used to create a new level with \ref setLevel() or 
	 * Level::name(). 
	 * 
	 * \return std::string the name of the level i.e. debug
	 */
    std::string name() const;

	/*!
	 * \brief Enum log level 
	 *  
	 * Returns the \ref Level::LogLevel enumerated value for the current 
	 * level. 
	 *  
	 * \note This value should not be saved to settings or anything as it 
	 * is subject to change between versions of the logger. 
	 *  
	 * \return LogLevel enum value representing the log level.
	 */
    LogLevel level() const;
    
	//! Checks if level has \a level
    bool hasLevel(const Level &level) const;

	//! Checks if level has \a level
    bool hasLevel(LogLevel level) const;

	//! Checks if level has fatal
    bool hasFatal() const;

	//! Checks if level has error
    bool hasError() const;

	//! Checks if level has warn
    bool hasWarn() const;

	//! Checks if level has info
    bool hasInfo() const;

	//! Checks if level has trace
    bool hasTrace() const;

	//! Checks if level has debug
    bool hasDebug() const;

	//! Checks if level has function tracing
    bool hasFuncTrace() const;

	//! Checks if level has all
    bool hasAll() const;

	//! Checks if level is empty
    bool hasNone() const;
    
	//! Compares 2 levels for equality
    bool operator==(const Level &lev);

	//! Compares 2 levels for inequality
    bool operator!=(const Level &lev);

	//! Compares 2 levels for difference
    bool operator<(const Level &lev);

	//! Compares 2 levels for difference
    bool operator>(const Level &lev);

	//! Compares 2 levels for difference
    bool operator<=(const Level &lev);

	//! Compares 2 levels for difference
    bool operator>=(const Level &lev);
    
private:
    LogLevel level_;
};
    
} // sharklog

#endif // level_H
