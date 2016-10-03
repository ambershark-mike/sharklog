
#include <iostream>
#include <sharklog/logger.h>
#include <sharklog/consoleoutputter.h>
#include <sharklog/standardlayout.h>

using namespace std;
using namespace sharklog;

int main(int ac, char **av)
{
	// setup logger
	auto root = Logger::rootLogger();
	root->setLayout(LayoutPtr(new StandardLayout));
	root->addOutputter(OutputterPtr(new ConsoleOutputter));

	// do some logging
	for (int i=0;i<1000;++i)
		root->log(Level::info(), "testing");

	return 0;
}

