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

#ifndef __layout_H
#define __layout_H

#include <string>
#include <memory>

struct tm;

namespace sharklog
{
    
class Level;
class Layout;
    
/*!
 * \var LayoutPtr
 *
 * A C++ shared_ptr pointer to a \ref Layout.
 *
 * To allocate this you would do:
 * @code
 * LayoutPtr p(new StandardLayout);
 * // or
 * auto p = std::make_shared<StandardLayout>();
 * @endcode
 */
using LayoutPtr = std::shared_ptr<Layout>;
    
/*!
 * @brief Base Layout
 * 
 * This is the base for all layout classes.  It can be allocated and passed around 
 * by using a \ref LayoutPtr. 
 *  
 * Any layouts you make will need to derive from this class. 
 *  
 * Layouts are responsible for how the data is formatted when it is sent to an 
 * \ref Outputter. 
 *  
 * See \ref StandardLayout for an example of a complete layout class. 
 *  
 */
class Layout
{
public:
	//! Destructor
    virtual ~Layout();
    
	/*!
	 * \brief Formats the log message 
	 *  
	 * This function is called to get the formatted log message. 
	 * In your derived class you will need to implement this function. 
	 *  
	 * The \a result parameter should contain your formatted string used for 
	 * logging. 
	 *  
	 * The other parameters, \a level, loggerName, logMessage, will all be 
	 * passed in to this function for use in your formatting. 
	 * 
	 * \param result output of the formatted string
	 * \param level the current \ref Level of the log message
	 * \param loggerName the name of the logger
	 * \param logMessage the message to be logged
	 */
    virtual void formatMessage(std::string &result, const Level &level, const std::string &loggerName, const std::string &logMessage) = 0;
    
	/*!
	 * \brief Gets the content type 
	 *  
	 * This should return the mime type or content-type for your return data. 
	 * Things like "text/plain" or "text/html" etc.
	 * 
	 * \return std::string the mime content-type for the data in result
	 */
    virtual std::string contentType() const;

	/*!
	 * \brief Adds the header 
	 *  
	 * This function will be called to add any header to the log message. 
	 *  
	 * For instance if you always wanted something like ">>" to be prepended 
	 * you could have your appendHeader function add a ">>" to the message; 
	 *  
	 * \note You should always append to the string \a result as it may
	 * already contain data. 
	 * 
	 * \param result The resulting string with appended header 
	 * \sa appendFooter 
	 */
    virtual void appendHeader(std::string &result);

	/*!
	 * \brief Adds the footer 
	 *  
	 * This function will be called to add the footer to the log message. 
	 *  
	 * \note You shoudl always append to the string \a result as it may 
	 * already contain data. 
	 *  
	 * \param result The resulting string with appended footer 
	 * \sa appendHeader 
	 */
    virtual void appendFooter(std::string &result);

protected:
	/*!
	 * \brief Formats a time string 
	 *  
	 * This is a convenience function to format a time string.  It uses 
	 * C library calls since the C++ put_time has pretty high version 
	 * compiler dependencies for some compilers. 
	 *  
	 * It takes the same format arguments as put_time or strftime in 
	 * \a format. 
	 *  
	 * It takes a tm struct pointer for the time you want to use, or 
	 * a null and it will get the current localtime. 
	 * 
	 * \param format string with format codes following strftime rules
	 * \param timeToUse a tm struct with the time in it
	 * 
	 * \return std::string a formatted time string
	 */
	std::string formatTime(const std::string &format, tm *timeToUse=0);
};
    
} // sharklog

#endif // layout_H
