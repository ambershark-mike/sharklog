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

#include "basicfileconfig.h"
#include "standardlayout.h"
#include "fileoutputter.h"

using namespace sharklog;

bool sharklog::BasicFileConfig::configure(const std::string &path, const Level &lev)
{
	return configure(Logger::rootLogger(), path, lev);
}

bool sharklog::BasicFileConfig::configure(const std::string &path, const std::string &logger, const Level &lev)
{
	return configure(Logger::logger(logger), path, lev);
}

bool sharklog::BasicFileConfig::configure(LoggerPtr logger, const std::string &path, const Level &lev)
{
	// don't bother with an empty path or an empty logger ptr
	if (path.empty() || !logger)
		return false;

	auto fop = std::make_shared<FileOutputter>(path);
	if (!fop->open()) 
		return false;
	fop->setLayout(std::make_shared<StandardLayout>());

	logger->setLevel(lev);
	logger->addOutputter(fop);

	return true;
}
