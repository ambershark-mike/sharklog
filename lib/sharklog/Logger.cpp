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
#include <algorithm>
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
    return fullName_;
}

LoggerPtr Logger::logger(const std::string &name)
{
    auto root = rootLogger();
    
    if (name.empty())
        return root;
    
    // check to see if we have this logger, or a parent for it
    auto tokens = UtilFunctions::split(name, '.');
    std::reverse(tokens.begin(), tokens.end());
    auto parent = root->findLogger(&tokens);
    if (parent && parent->name() == name)
    {
        // we found our logger
        return parent;
    }
    
    if (!parent)
        parent = root;
    
    // create the logger
    return parent->createLogger(name);
    //LoggerPtr logger(new Logger());
    //logger->setName(name);
    //logger->setParent(parent);
    //return logger;
}

LoggerPtr Logger::parent() const
{
    return parent_;
}

// takes a tokenized list (in reverse order), so com.ambershark.sharklog would be sharklog, ambershark, com
LoggerPtr Logger::findLogger(std::vector<std::string> *tokens) const
{
    if (tokens->empty())
        return LoggerPtr();
    
    for (auto it : children_)
    {
        if (it->name() == tokens->back())
        {
            // found a match, strip last token and call again
            tokens->pop_back();
            auto logptr = it->findLogger(tokens);
            
            // if we dont find the next token, return our current iterator LoggerPtr
            if (!logptr)
                return it;
            else // otherwise return the pointer it found
                return logptr;
        }
    }
    
    return LoggerPtr();
}

std::string Logger::baseName() const
{
    return baseName_;
}

void Logger::setName(const std::string &name)
{
    fullName_ = name;
    
    // set our short name
    auto base = name;
    if (base.back() == '.')
        base = name.substr(0, base.size()-1);
        
    auto pos = base.find_last_of('.');
    if (pos == string::npos || pos == base.size()-1)
        baseName_ = name;
    else
        baseName_ = base.substr(pos+1);
}

void Logger::setParent(LoggerPtr parent)
{
    parent_ = parent;
}

LoggerPtr Logger::createLogger(const std::string &name)
{
    vector<string> loggersToCreate;
    
    // get the loggers we need to create, taking out the full name of the loggers we have in this parent
    auto pos = name.find(this->name());
    if (pos != string::npos)
        loggersToCreate = UtilFunctions::split(name.substr(pos), '.');
    else
        loggersToCreate = UtilFunctions::split(name, '.');
    
    // we should have at least 1 logger to create
    assert(loggersToCreate.size());
    if (loggersToCreate.empty())
        return LoggerPtr();
    
    return createLoggers(&loggersToCreate);
}

LoggerPtr Logger::createLoggers(std::vector<std::string> *loggers)
{
    // create first logger, might want to reverse the vector for pop_back()
    // creating needs to set name, parent, add to children, etc, parent is this
    // call recursively with new pointer to create children loggers
    
    return sharklog::LoggerPtr();
}
