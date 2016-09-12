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

#include <assert.h>
#include <sstream>
#include <vector>
#include "Logger.h"
#include "UtilFunctions.h"

using namespace sharklog;
using namespace std;

LoggerPtr Logger::rootLogger_;

Logger::Logger()
{
}

Logger::~Logger()
{
}

LoggerPtr Logger::rootLogger()
{
    if (!rootLogger_)
    {
        LoggerPtr p(new Logger());
        rootLogger_ = p;
        assert(rootLogger_);
    }
    
    return rootLogger_;
}

bool Logger::isRoot() const
{
    // root loggers are the only ones without parents
    return !(bool)parent_;
}

std::string Logger::name() const
{
    return name_;
}

LoggerPtr Logger::logger(const std::string &name)
{
    auto root = rootLogger();
    
    if (name.empty())
        return root;
    
    if (root->hasChild(name))
    {
        // get the named logger
    }
    
    // create the logger
    LoggerPtr logger(new Logger());
    logger->name_ = name;
    logger->parent_ = root;
    return logger;
}

bool Logger::hasChild(const std::string &name)
{
    auto tokens = UtilFunctions::split(name, '.');
    return false;
}

LoggerPtr Logger::parent() const
{
    return parent_;
}
