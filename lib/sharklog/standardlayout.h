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

#ifndef __standardlayout_H
#define __standardlayout_H

#include <sharklog/sharklogdefs.h>
#include <sharklog/layout.h>
#include <string>

namespace sharklog
{
    
/*!
 * @brief Standard log layout
 * 
 * This is the standard layout (the default if you will) for the Logger. 
 * It has a format like so: 
 *  
 * \code 
 * // Date [MM/DD/YYYY] Time [HH:MM:SS.msec] Thread ID [0xff] Level [INFO] Log message
 * [01/20/2017][23:23:11.788][0x7f7a19143740][INFO] testing
 * \endcode 
 *  
 * All loggers must have a layout that derives from \ref Layout. 
 *  
 * When using a \ref BasicConfig or \ref BasicFileConfig this is the layout that 
 * is used. 
 */
class SHARKLOGAPI StandardLayout : public Layout
{
public:
	//! Destructor
    virtual ~StandardLayout();
    
	/*!
	 * \brief Layout formatMessage 
	 *  
	 * This is called by the Logger and is not used besides that. 
	 * 
	 */
    void formatMessage(std::string &result, const Level &level, const std::string &loggerName, const std::string &logMessage) override;
    
	/*!
	 * \brief Appends Header 
	 *  
	 * Called by the logger, not used outside of that. 
	 * 
	 */
    void appendHeader(std::string &result) override;

	/*!
	 * \brief Appends Footer
	 *  
	 * Called by the logger, not used manually. 
	 * 
	 */
    void appendFooter(std::string &result) override;
    
private:
    void setupDate(std::string &s);
    void setupTime(std::string &s);
    void setupThread(std::string &s);
};
    
} // sharklog

#endif // standardlayout_H
