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
 * @todo document
 */
class Layout
{
public:
    virtual ~Layout();
    
    virtual void formatMessage(std::string &result, const Level &level, const std::string &loggerName, const std::string &logMessage) = 0;
    
    virtual std::string contentType() const;
    virtual void appendHeader(std::string &result);
    virtual void appendFooter(std::string &result);

protected:
	std::string formatTime(const std::string &format, tm *timeToUse=0);
};
    
} // sharklog

#endif // layout_H
