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

#ifndef __level_H
#define __level_H

#include <string>

namespace sharklog
{
    
/*!
 * @brief Logger level
 *
 * @todo document this
 */
class Level
{
public:
    enum LogLevel
    {
        NONE
        , FATAL
        , ERROR
        , WARN
        , INFO
        , TRACE
        , DEBUG
        , FUNCTRACE
    };
    
    Level(LogLevel lev = NONE);
    
    static Level fatal();
    static Level error();
    static Level warn();
    static Level info();
    static Level trace();
    static Level debug();
    static Level functrace();
    
    std::string name() const;
    LogLevel level() const;
    
    bool hasLevel(const Level &level);
    bool hasLevel(LogLevel level);
    bool hasFatal();
    bool hasError();
    bool hasWarn();
    bool hasInfo();
    bool hasTrace();
    bool hasDebug();
    bool hasFuncTrace();
    
    bool operator==(const Level &lev);
    bool operator!=(const Level &lev);
    bool operator<(const Level &lev);
    bool operator>(const Level &lev);
    bool operator<=(const Level &lev);
    bool operator>=(const Level &lev);
    
private:
    LogLevel level_;
};
    
} // sharklog

#endif // level_H