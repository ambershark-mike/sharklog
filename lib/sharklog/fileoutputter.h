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
 * This outputter is used to write logs to a file.  To use the file outputter,
 * just add it to a Logger.  Here is an example of setting up a logger with a
 * file outputter:
 *
 * \code
 * // setup logger
 * auto log = Logger::rootLogger();
 * log->setLayout(LayoutPtr(new StandardLayout()));
 *
 * // setup our file
 * auto fop = new FileOutputter("/tmp/test.log");
 * if (!fop->open())
 *    return 1; // fail
 *
 * // add outputter to the logger
 * log->addOutputter(OutputterPtr(fop));
 * fop = nullptr; // clear this pointer since we handed it off to a smart one
 *
 * // log a message
 * SHARKLOG_TRACE(log, "hello log file");
 * \endcode
 */
class FileOutputter : public Outputter
{
public:
    /*!
     * @brief Constructor
     *
     * Creates a FileOutputter.  You can pass a parmater \a filename
     * which tells the class which path to write the log file to.
     *
     * This function calls @ref setFilename().
     *
     * @param filename the file path to the file you want to write
     * @sa setFilename()
     */
    FileOutputter(const std::string &filename = std::string());
    
    /*!
     * @brief Deconstructor
     */
    virtual ~FileOutputter();
    
    /*!
     * @brief Sets the file name/path
     *
     * Set the filename (and path) of the log file to write.  For example you can
     * have /tmp/myfile.log or just myfile.log to write to the current directory.
     *
     * Any call to this function will close an existing and open file, by calling
     * \ref close().
     *
     * @param filename the filename and path for the log file
     * @sa close()
     */
    void setFilename(const std::string &filename);
    
    /*!
     * @brief Gets the current filename
     *
     * Gets the file name and path for the current log file.
     *
     * @return the filename for the log file
     */
    std::string filename() const;
    
    /*!
     * @brief Set append file mode
     *
     * Sets whether or not the file should be appended or truncated when
     * opened.
     *
     * The default is truncate mode.
     *
     * Set to true in order to append when opening.  This value is only used
     * when opening the file.
     *
     * @param append true to append, false to truncate
     * @sa append(), open()
     */
    void setAppend(bool append);
    
    /*!
     * @brief Get append mode
     *
     * Returns the current value of append mode.
     *
     * @return bool representing the append mode
     */
    bool append() const;
    
    /*!
     * @brief Open the log file
     *
     * This opens the log file.  Filename should be set already by now via the
     * constructor or \ref setFilename().
     *
     * @return true if opened, false if failed
     */
    virtual bool open() override;
    
    /*!
     * @brief Write a log message
     *
     * Called to write \a logMessage to the log file.
     *
     * Logger should be open or this log message will be discarded.
     *
     * @param logMessage The message to log
     * @sa open()
     */
    virtual void writeLog(const Level &lev, const std::string &loggerName, const std::string &logMessage, const Location &loc) override;
    
    /*!
     * @brief Close the log file
     *
     * Closes the log file.  It must be reopened before you log again or the
     * messages will be lost.
     *
     * @sa open()
     */
    virtual void close() override;
    
    /*!
     * @brief Checks file open status
     *
     * Checks to see if the file is open.
     *
     * @return true if open, false if not
     * @sa open()
     */
    virtual bool isOpen() const override;
    
private:
    std::ofstream file_;
    std::string filename_;
    bool append_;
    static std::recursive_mutex mutex_;
};
    
} // sharklog

#endif // fileoutputter_H
