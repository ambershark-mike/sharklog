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

#ifndef __location_H
#define __location_H

#include <sharklog/sharklogdefs.h>
#include <string>

namespace sharklog
{
    
/*!
 * @brief Location
 * 
 * This class is used for tracking location of log messages 
 * inside a code file. 
 *  
 * In combination with the SHARKLOG_LOCATION macro it will 
 * hold the proper file, line, and function information for 
 * use in logging a message. 
 *  
 * If using the logging macros like SHARKLOG_DEBUG() they will 
 * automatically include location. 
 *  
 * Likewise when using a \ref LoggerStream and ending it with 
 * a SHARKLOG_END, that will include location information as well. 
 *  
 * You should not need to allocate or use this class in your logging. 
 */
class SHARKLOGAPI Location
{
public:
	//! Default constructor
    Location() : line_(0) { }

	/*!
	 * \brief Overloaded constructor 
	 *  
	 * This constructor will build a Location object with the appropriate 
	 * \a file, \a function, and \a line. 
	 * 
	 * \param file the file we are located in, i.e. __FILE__
	 * \param function the current function, i.e. in gcc __PRETTY_FUNCTION__
	 * \param line the current line of code, i.e. __LINE__
	 */
    Location(const std::string &file, const std::string &function, int line);
    
	/*!
	 * \brief Checks if location is set 
	 *  
	 * This will check whether or not we have location data.  Returns 
	 * true if we are empty, i.e. no data, false if not. 
	 *  
	 * Similar to std lib empty() functions. 
	 * 
	 * \return bool true if empty, false if we have loc data
	 */
    bool empty() const;
    
	/*!
	 * \brief Current file 
	 *  
	 * This returns the currently set file location as a string. 
	 * 
	 * \return std::string file location
	 */
    inline std::string file() const { return file_; }

	/*!
	 * \brief Current function 
	 *  
	 * This returns the current function location as a string. 
	 * 
	 * \return std::string function location
	 */
    inline std::string function() const { return function_; }

	/*!
	 * \brief Current line 
	 *  
	 * This returns the current line of code. 
	 * 
	 * \return int current line location
	 */
    inline int line() const { return line_; }
    
	/*!
	 * \brief Formatted location string 
	 *  
	 * This returns a formatted location string.  It is formatted like 
	 * File: <file> Function: <func> Line: <line>. 
	 * 
	 * \return std::string formatted location information
	 */
    std::string formattedString() const;
    
private:
    std::string file_;
    std::string function_;
    int line_;
};
    
} // sharklog

/*! 
  The following macro and defines section is used to define
  different location information in different compilers, like
  msvc, mingw, gcc, and clang.
  */
#if !defined(SHARKLOG_LOCATION)
    #if defined(_MSC_VER)
        #if _MSC_VER >= 1300
            #define __SHARKLOG_FUNC__ __FUNCSIG__
        #endif
    #else
        #if defined(__GNUC__)
            #define __SHARKLOG_FUNC__ __PRETTY_FUNCTION__
        #endif
    #endif

    #if !defined(__SHARKLOG_FUNC__)
        #define __SHARKLOG_FUNC__ ""
    #endif

	//! This macro is used to generate location information for the logger, see \ref Location
    #define SHARKLOG_LOCATION sharklog::Location(__FILE__, __SHARKLOG_FUNC__, __LINE__)
#endif

#endif // location_H
