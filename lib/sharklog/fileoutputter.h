////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2016, by Ambershark, LLC.
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

#ifndef __fileoutputter_H
#define __fileoutputter_H

#include <sharklog/outputter.h>
#include <string>
#include <fstream>
#include <mutex>

namespace sharklog
{
    
/*!
 * \brief File outputter
 *
 * \todo document this
 */
class FileOutputter : public Outputter
{
public:
    FileOutputter(const std::string &filename = std::string());
    virtual ~FileOutputter();
    
    void setFilename(const std::string &filename);
    std::string filename() const;
    
    void setAppend(bool append);
    bool append() const;
    
    virtual bool open() override;
    virtual void writeLog(const std::string &logMessage) override;
    virtual void close() override;
    
    virtual bool isOpen() const override;
    
private:
    std::ofstream file_;
    std::string filename_;
    bool append_;
    static std::recursive_mutex mutex_;
};
    
} // sharklog

#endif // fileoutputter_H
