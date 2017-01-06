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

#include "level.h"
#include <map>

using namespace sharklog;
using namespace std;

Level::Level(Level::LogLevel lev) : level_(lev)
{
}

Level::LogLevel Level::level() const
{
    return level_;
}

Level Level::fatal()
{
    return Level(FATAL);
}

Level Level::error()
{
    return Level(ERROR);
}

Level Level::warn()
{
    return Level(WARN);
}

Level Level::info()
{
    return Level(INFO);
}

Level Level::trace()
{
    return Level(TRACE);
}

Level Level::debug()
{
    return Level(DEBUG);
}

Level Level::functrace()
{
    return Level(FUNCTRACE);
}

std::string Level::name() const
{
    static map<LogLevel, string> levelNames;
    if (levelNames.empty())
    {
        levelNames[NONE] = "NONE";
        levelNames[FATAL] = "FATAL";
        levelNames[ERROR] = "ERROR";
        levelNames[WARN] = "WARN";
        levelNames[INFO] = "INFO";
        levelNames[TRACE] = "TRACE";
        levelNames[DEBUG] = "DEBUG";
        levelNames[FUNCTRACE] = "FUNC";
        levelNames[ALL] = "ALL";
    }
    
    return levelNames.at(level_);
}

bool Level::hasLevel(const Level &level) const
{
    return hasLevel(level.level());
}

bool Level::hasFatal() const
{
    return hasLevel(FATAL);
}

bool Level::hasError() const
{
    return hasLevel(ERROR);
}

bool Level::hasWarn() const
{
    return hasLevel(WARN);
}

bool Level::hasInfo() const
{
    return hasLevel(INFO);
}

bool Level::hasTrace() const
{
    return hasLevel(TRACE);
}

bool Level::hasDebug() const
{
    return hasLevel(DEBUG);
}

bool Level::hasFuncTrace() const
{
    return hasLevel(FUNCTRACE);
}

bool Level::hasLevel(LogLevel level) const
{
    return (level <= level_);
}

bool Level::operator==(const Level &lev)
{
    return (level_ == lev.level());
}

bool Level::operator!=(const Level &lev)
{
    return (level_ != lev.level());
}

bool Level::operator<(const Level &lev)
{
    return (level_ < lev.level());
}

bool Level::operator>(const Level &lev)
{
    return (level_ > lev.level());
}

bool Level::operator<=(const Level &lev)
{
    return (level_ <= lev.level());
}

bool Level::operator>=(const Level &lev)
{
    return (level_ >= lev.level());
}

Level Level::all()
{
    return Level(ALL);
}

bool Level::hasAll() const
{
    return hasLevel(ALL);
}

bool Level::hasNone() const
{
    return hasLevel(NONE);
}
