////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2017, by Ambershark, LLC.
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

#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#include <thread>
#include <sstream>
#include <map>
#include <sharklog/logger.h>
#include <sharklog/consoleoutputter.h>
#include <sharklog/standardlayout.h>
#include <sharklog/fileoutputter.h>
#include <sharklog/functrace.h>

using namespace std;
using namespace sharklog;

std::map<int, std::string> threadResults_;

void usage();
int threadTest(const std::string &filename="");
int basicTest();

int main(int ac, char **av)
{
    if (ac == 1)
    {
        usage();
        return 1;
    }
    else
    {
        // we have command line params
        list<string> params;
        for (auto i=0;i<ac;++i)
            params.push_back(av[i]);
        
        if (find(params.begin(), params.end(), "--help") != params.end())
        {
            usage();
            return 1;
        }
        
        if (find(params.begin(), params.end(), "-t") != params.end())
        {
            return threadTest();
        }

        if (find(params.begin(), params.end(), "-ft") != params.end())
        {
			return threadTest("file-thread-test.tmp");
        }
        
        if (find(params.begin(), params.end(), "-b") != params.end())
        {
            return basicTest();
        }
    }

	return 0;
}

void funcTracePart3()
{
    SHARKLOG_FUNCTRACE_ROOT;
}

void funcTracePart2()
{
    SHARKLOG_FUNCTRACE(Logger::rootLogger());
    SHARKLOG_TRACE(Logger::rootLogger(), "inside functrace part 2");
}

void funcTraceTest()
{
    SHARKLOG_FUNCTRACE_ROOT;
    SHARKLOG_INFO(Logger::rootLogger(), "inside the functrace test");
    funcTracePart2();
}

int basicTest()
{
    // setup logger
    auto root = Logger::rootLogger();
    root->setLayout(LayoutPtr(new StandardLayout));
    root->addOutputter(OutputterPtr(new ConsoleOutputter));
    
    // do some logging
    //for (int i=0;i<1000;++i)
    root->log(Level::info(), "testing");
    
    // test functrace
    funcTraceTest();
    
    FuncTrace::setEnterHeader("==>");
    FuncTrace::setExitHeader("<==");
    funcTracePart3();
    
    return 0;
}

void usage()
{
    cout << "loggertest [options]" << endl << endl;
    
    cout << "   --help                 Shows this help" << endl;
    cout << endl;
    cout << "Tests:" << endl;
    cout << "   -t                     Run threading test" << endl;
	cout << "   -ft                    Run threading test with files" << endl;
    cout << "   -b                     Basic logger test" << endl;
    
    cout << endl;
}

void run(int tnum)
{
    stringstream result;
    
    unsigned int count = 1000;
    auto logger = Logger::rootLogger();
    
    std::list<string> logs;
    for (unsigned int i=0;i<count;++i)
    {
        stringstream ss;
        ss << "thread #" << tnum << " iter " << i;
        logger->log(Level::info(), ss.str());
        logs.push_back(ss.str());
    }
    
    if (logs.size() != count)
    {
        result << "=======> FAILED VERIFY OF THREAD " << tnum << " expected " << count << " and logged " << logs.size() << endl;
        threadResults_[tnum] = result.str();
        return;
    }
    
    int c = 0;
    for (auto it : logs)
    {
        stringstream ss;
        ss << "thread #" << tnum << " iter " << c++;
        if (it != ss.str())
        {
            result << "=======> FAILED VERIFY OF THREAD " << tnum << " item [" << it << "] and it should be [" << ss.str() << "]" << endl;
            threadResults_[tnum] = result.str();
            return;
        }
    }
    
    result << "=======> THREAD " << tnum << " OK" << endl;
    threadResults_[tnum ] = result.str();
}

int threadTest(const std::string &filename)
{
    threadResults_.clear();
    
    auto root = Logger::rootLogger();
    root->setLayout(LayoutPtr(new StandardLayout));

	if (filename.empty())
	{
		root->addOutputter(OutputterPtr(new ConsoleOutputter));
	}
	else
	{
		OutputterPtr fop(new FileOutputter(filename));
		if (!fop->open())
		{
			cout << "Failed to open file " << filename << endl;
			return 1;
		}
		root->addOutputter(fop);
	}
    
    cout << "Starting threads...." << endl;
    unsigned int numThreads = 10;
    
    std::list<thread> threads;
    for (unsigned int i=0;i<numThreads;++i)
    {
        threads.push_back(thread(run, i));
    }
    
    for (auto &it : threads)
        it.join();
    
    if (threadResults_.size() != numThreads)
        cout << "=======> NOT ENOUGH THREADS REPORTED RESULTS!!!" << endl;
    
    for (auto it : threadResults_)
        cout << it.second;
    
    return 0;
}
