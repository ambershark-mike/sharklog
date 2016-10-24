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

#ifndef __location_H
#define __location_H

#include <string>

namespace sharklog
{
    
/*!
 * @brief Location
 *
 * @todo document this
 */
class Location
{
public:
    Location() : line_(0) { }
    Location(const std::string &file, const std::string &function, int line);
    
    bool empty() const;
    
    inline std::string file() const { return file_; }
    inline std::string function() const { return function_; }
    inline int line() const { return line_; }
    
    std::string formattedString() const;
    
private:
    std::string file_;
    std::string function_;
    int line_;
};
    
} // sharklog

//! \todo Document SHARKLOG_LOCATION
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

    #define SHARKLOG_LOCATION sharklog::Location(__FILE__, __SHARKLOG_FUNC__, __LINE__)
#endif

#endif // location_H
