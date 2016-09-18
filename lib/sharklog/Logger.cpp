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
#include <iostream>

using namespace sharklog;
using namespace std;

LoggerPtr Logger::rootLogger_;
Logger::LoggerMap Logger::allNamedLoggers_;

Logger::Logger()
{
    //std::cout << "create logger " << this << endl;
}

Logger::~Logger()
{
    //std::cout << "decon logger " << this << " name " << name() << endl;
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
    // find our if we have this logger already
    auto logger = allNamedLoggers_.find(name);
    if (logger != allNamedLoggers_.end())
        return logger->second;
    
    // create the logger since we don't have it
    return rootLogger()->createLoggers(name);
}

LoggerPtr Logger::parent() const
{
    return parent_;
}

std::string Logger::baseName() const
{
    return baseName_;
}

void Logger::closeRootLogger()
{
    if (!rootLogger_)
        return;
    
    //cout << "closing root" << endl;
    closeLogger(rootLogger_);
    
    allNamedLoggers_.clear();
    rootLogger_.reset();
}

LoggerPtr Logger::createLoggers(const std::string &loggerName)
{
    // make sure we don't have this named logger already
    assert(allNamedLoggers_.find(loggerName) == allNamedLoggers_.end());
    
    // find our parent logger and which loggers we need to create.
    vector<string> loggersToCreate;
    auto parent = findParent(loggerName);
    auto pos = loggerName.find(parent->name());
    if (pos != string::npos)
        loggersToCreate = UtilFunctions::split(loggerName.substr(pos), '.');
    else
        loggersToCreate = UtilFunctions::split(loggerName, '.');
    
    // create all our loggers
    for (auto it : loggersToCreate)
    {
        parent = createLogger(parent, it);
    }
    
    return parent;
}

LoggerPtr Logger::findParent(const string &loggerName)
{
    // do we have any . delimiters, if not, parent is root
    if (loggerName.find('.') == string::npos)
        return rootLogger();
    
    // find our lowest parent
    LoggerPtr parent;
    string s = loggerName;
    while (s.find('.') != string::npos)
    {
        s = UtilFunctions::stripLastToken(s, '.');
        auto it = allNamedLoggers_.find(s);
        if (it != allNamedLoggers_.end())
        {
            parent = it->second;
            break;
        }
    }
    
    if (!parent)
        parent = rootLogger();
    
    return parent;
}

LoggerPtr Logger::createLogger(LoggerPtr parent, const std::string &baseName)
{
    assert(parent);
    assert(baseName.size());
    
    // create our full name
    stringstream ss;
    if (!parent->isRoot())
        ss << parent->name() << "." << baseName;
    else
        ss << baseName;
    
    auto fullName = ss.str();
    
    // make sure we don't have this logger already
    assert(allNamedLoggers_.find(fullName) == allNamedLoggers_.end());
    
    // create the logger
    LoggerPtr logger(new Logger());
    logger->parent_ = parent;
    logger->setName(fullName, baseName);
    logger->allNamedLoggers_[fullName] = logger;
    parent->children_.push_back(logger);
    
    return logger;
}

void Logger::setName(const std::string &loggerName, const std::string &baseName)
{
    fullName_ = loggerName;
    baseName_ = baseName;
    //cout << "logger " << this << " named " << fullName_ << endl;
}

bool Logger::hasLogger(const std::string &name)
{
    return (allNamedLoggers_.find(name) != allNamedLoggers_.end());
}

unsigned int Logger::count()
{
    if (!rootLogger_)
        return 0;
    
    return (unsigned int)rootLogger()->allNamedLoggers_.size() + 1;
}

void Logger::closeLogger(LoggerPtr logger)
{
    assert(logger);
    
    // clean up children
    for (auto it : logger->children_)
        closeLogger(it);
    
    logger->children_.clear();
    
    // clean up logger
    logger->parent_.reset();
    logger->allNamedLoggers_[logger->name()].reset();
}
