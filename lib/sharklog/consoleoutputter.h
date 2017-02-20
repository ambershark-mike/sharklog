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

#ifndef __consoleoutputter_H
#define __consoleoutputter_H

#include <sharklog/sharklogdefs.h>
#include <sharklog/outputter.h>
#include <mutex>

namespace sharklog
{
    
/*!
 * \brief Console output
 *  
 * This outputter logs to the console on stdout. 
 *  
 * It is the default outputter of \ref BasicConfig and one of 
 * the most common outputters. 
 *  
 * It helps with console debugging while developing as well as 
 * for end users to see any warnings/error issues that might pop 
 * up. 
 */
class SHARKLOGAPI ConsoleOutputter : public Outputter
{
public:
	//! Constructor
    ConsoleOutputter();
    
	/*!
	 * \brief Opens the outputter 
	 *  
	 * This function is not used on the console outputter and will 
	 * always return true. 
	 * 
	 * \return bool true (always)
	 */
    bool open() final;

	/*!
	 * \brief Close outputter 
	 *  
	 * This function is not used on the console outputter. 
	 * 
	 */
    void close() final;

	//! Writes the log message to the console
    void writeLog(const Level &lev, const std::string &loggerName, const std::string &message, const Location &loc) final;
    
	//! Always returns true, not used
    bool isOpen() const final;
    
	/*!
	 * \brief Sets usage of stdout 
	 *  
	 * This function will set whether or not this console outputter 
	 * will log to stdout.  By default this is true.
	 * 
	 * \param use false to not log to stdout, true to log 
	 * \sa setUseStdErr() 
	 */
    void setUseStdOut(bool use);

	/*!
	 * \brief Gets stdout usage 
	 *  
	 * This function will return true if this console outputter is 
	 * currently allowed to log to stdout and false if not. 
	 * 
	 * \return bool true if using stdout, false if not
	 * \sa useStdErr()
	 */
    bool useStdOut() const;
    
	/*!
	 * \brief Sets stderr usage
	 *  
	 * This function sets whether or not the console outputter will 
	 * log to stderr.  By default this is false. 
	 * 
	 * \param use true to turn on stderr, false to turn off
	 */
    void setUseStdErr(bool use);

	/*!
	 * \brief Gets stderr usage 
	 *  
	 * Gets whether or not this outputter is allowed to log to stderr. 
	 *  
	 * \return bool true allowed to use stderr, false if not
	 */
    bool useStdErr() const;
    
private:
    bool useStdOut_;
    bool useStdErr_;
    static std::mutex mutex_;
};
    
} // sharklog

#endif // consoleoutputter_H
