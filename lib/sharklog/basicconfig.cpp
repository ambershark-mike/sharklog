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
// You should have received a copy of the GNU Lesser General Public
// License along with this program.  If not see
// <http://www.gnu.org/licenses>.
//
// This notice must remain in the source code and any derived source.
//
////////////////////////////////////////////////////////////////////////////////

#include "basicconfig.h"
#include "logger.h"
#include "consoleoutputter.h"
#include "standardlayout.h"

using namespace sharklog;

void sharklog::BasicConfig::configure()
{
	auto root = Logger::rootLogger();
	auto op = std::make_shared<ConsoleOutputter>();
	op->setLayout(std::make_shared<StandardLayout>());
	root->addOutputter(op);
}

void sharklog::BasicConfig::configure(const Level &level)
{
	configure();
	auto root = Logger::rootLogger();
	root->setLevel(level);
}

void sharklog::BasicConfig::configure(const std::string &name)
{
	auto logger = Logger::logger(name);
	auto op = std::make_shared<ConsoleOutputter>();
	op->setLayout(std::make_shared<StandardLayout>());
	logger->addOutputter(op);
}

void sharklog::BasicConfig::configure(const std::string &name, const Level &level)
{
	configure(name);
	Logger::logger(name)->setLevel(level);
}
