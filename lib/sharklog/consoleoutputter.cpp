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

#include "consoleoutputter.h"
#include <iostream>

using namespace sharklog;
using namespace std;

std::mutex ConsoleOutputter::mutex_;

ConsoleOutputter::ConsoleOutputter()
    : useStdOut_(true)
    , useStdErr_(false)
{
}

bool ConsoleOutputter::open()
{
    return true;
}

void ConsoleOutputter::close()
{
}

bool ConsoleOutputter::isOpen() const
{
    return true;
}

void ConsoleOutputter::writeLog(const Level &lev, const std::string &loggerName, const std::string &message, const Location &loc)
{
    if (!isValid())
        return;
    
    lock_guard<mutex> lock(mutex_);
    
    string log;
    layout()->appendHeader(log);
    layout()->formatMessage(log, lev, loggerName, message);
    layout()->appendFooter(log);
    
    if (useStdErr_)
        cerr << log;
    
    if (useStdOut_)
        cout << log;
    
    cerr.flush();
    cout.flush();
}

void ConsoleOutputter::setUseStdOut(bool use)
{
    useStdOut_ = use;
}

bool ConsoleOutputter::useStdOut() const
{
    return useStdOut_;
}

void ConsoleOutputter::setUseStdErr(bool use)
{
    useStdErr_ = use;
}

bool ConsoleOutputter::useStdErr() const
{
    return useStdErr_;
}
