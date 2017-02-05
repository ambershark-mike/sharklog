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

#ifndef basicfileconfig_H
#define basicfileconfig_H

#include <string>
#include <sharklog/level.h>
#include <sharklog/logger.h>

namespace sharklog
{

/*!
 * \brief Basic File Configuration 
 *  
 * This class can be used to set up a basic configuration for the logger to 
 * output to files.
 * It adds a \ref FileOutputter and a \ref StandardLayout to either the root 
 * or a named logger. 
 *  
 * It sets the output \ref Level to ALL by default.  This can be overridden with 
 * the overloaded \ref configure(). 
 *  
 * If you don't want to use the root logger, you can use this to quickly configure 
 * a named logger.  Just use the overloaded \ref configure() function.
 *  
 * Example: 
 * \code 
 * // create a simple default logger 
 * BasicFileConfig::configure("myfile");
 *  
 * // create a new named logger 
 * BasicFileConfig::configure("myfile", "com.ambershark.named"); 
 *  
 * // create a default logger with an error only level 
 * BasicFileConfig::configure("myfile", Level::error()); 
 *  
 * // create a named logger with a specific level 
 * BasicFileConfig::configure("myfile", "com.ambershark.named", Level::info()); 
 * \endcode 
 *  
 */
class BasicFileConfig
{
public:
	/*!
	 * \brief Configures the logger
	 *  
	 * This function will configure the root logger with a specific log file at 
	 * \a path.  You can overload \a lev as well, the default is ALL. 
	 *  
	 * \param path The path of the log file
	 * \param lev The level of the logger
	 * 
	 * \return bool true on success, false on fail to open log file
	 */
	static bool configure(const std::string &path, const Level &lev = Level::all());

	/*!
	 * \brief Configures the logger
	 *  
	 * This function will configure a named logger with a specific log file 
	 * at \a path.  You can overload \a lev as well, the default is ALL. 
	 *  
	 * The \a logger parameter contains the name of the \ref Logger. 
	 *  
	 * \param path the path of the log file
	 * \param logger the name of the logger
	 * \param lev the logger level
	 * 
	 * \return bool true on success, false on fail to open
	 */
	static bool configure(const std::string &path, const std::string &logger, const Level &lev = Level::all());

private:
	static bool configure(LoggerPtr logger, const std::string &path, const Level &lev);
}; 

} // sharklog

#endif /* basicfileconfig_H */
