
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

using namespace std;
using namespace sharklog;

std::map<int, std::string> threadResults_;

void usage();
int threadTest();

int main(int ac, char **av)
{
    if (ac > 1)
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
    }
    
	// setup logger
	auto root = Logger::rootLogger();
	root->setLayout(LayoutPtr(new StandardLayout));
	root->addOutputter(OutputterPtr(new ConsoleOutputter));

	// do some logging
	//for (int i=0;i<1000;++i)
    root->log(Level::info(), "testing");

	return 0;
}

void usage()
{
    cout << "loggertest [options]" << endl << endl;
    
    cout << "   --help                 Shows this help" << endl;
    cout << "   -t                     Run threading test" << endl;
    
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

int threadTest()
{
    threadResults_.clear();
    
    auto root = Logger::rootLogger();
    root->setLayout(LayoutPtr(new StandardLayout));
    root->addOutputter(OutputterPtr(new ConsoleOutputter));
    
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
