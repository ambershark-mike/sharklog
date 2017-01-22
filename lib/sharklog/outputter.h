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
// You sould have received a copy of the GNU Lesser General Public
// License along with this program.  If not see
// <http://www.gnu.org/licenses>.
//
// This notice must remain in the source code and any derived source.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __outputter_H
#define __outputter_H

#include <string>
#include <memory>

namespace sharklog
{

class Outputter;

/*!
 * \var OutputterPtr
 *
 * A pointer to an \ref Outputter.
 */
using OutputterPtr = std::shared_ptr<Outputter>;
    
/*!
 * @brief Base Outputter
 * 
 * All outputters are derived from this base.  They must implement open(), 
 * close() and writeLog(). 
 *  
 * isOpen() is a virtual that can be overriden based on your needs.  By 
 * default it returns false. 
 *  
 * For an example of an Outputter derived class look at \ref ConsoleOutputter 
 * or \ref FileOutputter. 
 *  
 */
class Outputter
{
public:
	//! Destructor
    virtual ~Outputter();
    
	/*!
	 * \brief Opens the outputter 
	 *  
	 * The logger will call this function to open the Outputter.  Some 
	 * outputters do not need to be opened as is the case with 
	 * \ref ConsoleOutputter.  However ones like \ref FileOutputter 
	 * not only need to open, they need to succeed at opening. 
	 *  
	 * If your outputter does not need this, reimplement and have it 
	 * always return true. 
	 * 
	 * \return bool true if successfully opened, false if not
	 */
    virtual bool open() = 0;

	/*!
	 * \brief Writes a log message 
	 *  
	 * This function is called by the logger to write a log message 
	 * \a logMessage.  Your outputter should take this string and log 
	 * it however you want. 
	 * 
	 * \param logMessage the string to log
	 */
    virtual void writeLog(const std::string &logMessage) = 0;

	/*!
	 * \brief Closes the outputter 
	 *  
	 * The logger calls this function to close your outputter.  It must 
	 * exist but does not need to do anything. 
	 * 
	 */
    virtual void close() = 0;
    
	/*!
	 * \brief Check open status 
	 *  
	 * This will return true if the outputter is open, false if not. 
	 * 
	 * \return bool true if open, false if not
	 */
    virtual bool isOpen() const;
};
    
} // sharklog

#endif // outputter_H
