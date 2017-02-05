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

#ifndef basicconfig_H
#define basicconfig_H

#include <string>

namespace sharklog
{

class Level;

/*!
 * \brief Basic Configuration 
 *  
 * This class can be used to set up a basic configuration for the logger.  It 
 * uses the root logger and adds a \ref ConsoleOutputter and a \ref StandardLayout. 
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
 * BasicConfig::configure();
 *  
 * // create a new named logger 
 * BasicConfig::configure("com.ambershark.named"); 
 *  
 * // create a default logger with an error only level 
 * BasicConfig::configure(Level::error()); 
 *  
 * // create a named logger with a specific level 
 * BasicConfig::configure("com.ambershark.named", Level::info()); 
 * \endcode 
 *  
 */
class BasicConfig
{
public:
	/*!
	 * \brief Configure a basic console logger 
	 *  
	 * Configure the root logger to use the console and support all logging levels. 
	 * 
	 */
	static void configure();

	/*!
	 * \brief Configure console logger at specific level 
	 *  
	 * Configures a console root logger at a specific \a level. 
	 * 
	 * \param level The \ref Level to use for the logger.
	 */
	static void configure(const Level &level);

	/*!
	 * \brief Configure specific logger 
	 *  
	 * Configures a named logger for all logger levels.
	 * 
	 * \param name The named logger to create
	 */
	static void configure(const std::string &name);

	/*!
	 * \brief Configure specific logger at level
	 *  
	 * Configures a specific named logger at a specific logging level. 
	 * 
	 * \param name the name of the logger
	 * \param level the supported \ref Level
	 */
	static void configure(const std::string &name, const Level &level);
}; 

} // sharklog

#endif /* basicconfig_H */
