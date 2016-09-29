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

#ifndef __Logger_H
#define __Logger_H

#include <sharklog/level.h>
#include <string>
#include <memory>
#include <list>
#include <vector>
#include <sstream>
#include <map>

/*!
 * The main namespace of the SharkLog project.
 *
 * Everything will be protected by this namespace.
 */
namespace sharklog
{
    
class Logger;
    
/*!
 * \var LoggerPtr
 *
 * A pointer to a \ref Logger instance.
 */
using LoggerPtr = std::shared_ptr<Logger>;
    
/*!
 * \brief Logger instance
 *
 * This class covers the logger creation and interface into the SharkLog system.
 *
 * \todo example usage of logger
 */
class Logger
{
    using LoggerList = std::list<LoggerPtr>;
    using LoggerMap = std::map<std::string, LoggerPtr>;
    
public:
    virtual ~Logger();
    
    /*!
     * \brief Gets a pointer to the root logger
     *
     * If the root logger hasn't been created yet it will be created when this
     * function is called.
     *
     * The root logger is a static object so it will be persistent across your entire
     * project once it has been created with a call to this function.
     *
     * It is likely this function was called during configuration of the logger, so it
     * is quite rare for the root logger not to exist very early in your application.
     *
     * The root logger will have a blank \ref name().  You can test if a Logger is the
     * root by calling \ref isRoot().
     *
     * @return Pointer to the root logger.
     * \sa isRoot()
     */
    static LoggerPtr rootLogger();
    
    /*!
     * \brief Gets a pointer to a named logger
     *
     * Get a pointer to a Logger named \a name.  If the named logger does not exist, it
     * will be created for you.
     *
     * If the \a name param is empty or blank it will return the \ref rootLogger().
     *
     * \note Names are NOT case sensitive.
     *
     * \warning Logger names with trailing or extra periods will have the periods stripped.
     * So *com.* is the same as *com* ,  *x..y.z* is the same as *x.y.z*, and a name
     * of '.' is equivalent to an empty name.
     *
     * Loggers will inherit properties from their parents.  Parents are determined by the
     * name of the logger.  Using Java style naming i.e. com.company.product.logger.child,
     * you can create a parent child relationship between Loggers.  Properties inherited are
     * levels, outputters, and formatter.  This inheritance only happens if no level is set.
     *
     * In the above name example, the *child* logger would inherit from *logger* which would
     * in turn inherit from *product*, which inherits from *company*, which inherited
     * from *com*.  And finally *com* inherited from *root*.
     *
     * All Loggers inherit from the \ref rootLogger().
     *
     * *Example of inheritance*:
     *
     * | Name | Level | Inherited? |
     * | ---- | ----- | ---------- |
     * | Root | Root | No |
     * | com  | Root | Yes |
     * | com.company | Root | Yes |
     * | com.company.product | X | No |
     * | com.company.product.logger | X | Yes |
     * | com.company.product.logger.2 | Y | No |
     *
     * @param name The name of the logger you wish to obtain
     * @return A pointer to the Logger.
     * \sa rootLogger(), name()
     */
    static LoggerPtr logger(const std::string &name);
    
    /*!
     * @brief Check to see if a named logger exists
     *
     * Checks the list of named loggers to see if \a name exists.  This works like
     * @ref logger() but without creating the logger if it doesn't exist already.
     *
     * @note Can not find the root logger using a blank name.  This only applies to
     * named loggers.
     *
     * @param name the name of the logger to find
     * @return true if exists, false if not
     * @sa logger()
     */
    static bool hasLogger(const std::string &name);
    
    /*!
     * @brief Total allocated loggers
     *
     * Returns the total number of allocated loggers, including root.
     *
     * This function does not call @ref rootLogger() so it can be 0.
     *
     * @return number of allocated loggers
     */
    static unsigned int count();
    
    /*!
     * \brief Checks if this logger is the root logger
     *
     * @return True if this is the root logger, false if not.
     */
    bool isRoot() const;
    
    /*!
     * \brief Gets the full name of the logger
     *
     * Returns the name of this logger.  Name will be blank if it is the root logger.
     * No other loggers can be created with a blank name.
     * You can test if it's the root logger with \ref isRoot().
     *
     * If you want just the base name, i.e. the final token/part in the name, use
     * \ref baseName().
     *
     * @return The name of this logger.
     * \sa logger(), baseName()
     */
    std::string name() const;
    
    /*!
     * \brief Gets the short/base name of the logger
     *
     * \todo finish docs here
     *
     * This gives you the last piece of a name in case of a tokenized logger with parents.
     * So if you had com.ambershark.sharklog as the name, this function would give you
     * just *sharklog*.  If you want the full name, see \ref fullName().
     *
     * @return The base name
     * @sa logger(), name()
     */
    std::string baseName() const;
    
    /*!
     * \brief Gets the parent Logger
     *
     * If there is a parent logger (i.e. rootLogger() does not have one), then the parent
     * Logger is returned.
     *
     * @return A pointer to the parent logger.
     */
    LoggerPtr parent() const;
    
    /*!
     * @brief Closes the root logger
     *
     * This will close the root logger and all it's children.  This effectively closes all
     * the loggers.  It is the same as calling \ref closeLogger(rootLogger()).
     *
     * \note This does not guarantee all loggers will be closed as the logger system uses
     * smart pointers, so until everything releases their pointers the loggers will stay
     * open.  However, any new calls to \ref rootLogger() will create a new root logger
     * and it will have to be configured again.
     *
     * @sa closeLogger()
     */
    static void closeRootLogger();
    
    /*!
     * @brief Closes the logger
     *
     * This will close the logger specified in the \a logger parameter.  It will close all of
     * it's children as well.
     *
     * See the note in \ref closeRootLogger() for information on actually freeing the loggers.
     *
     * @param logger pointer to the logger to close
     * @sa closeRootLogger()
     */
    static void closeLogger(LoggerPtr logger);
    
    /*!
     * @brief Gets the current Level
     *
     * This will return the current \ref Level of the \ref Logger.  This level is inherited see
     * \ref Inheritance for more information.
     *
     * @return the current Level of the logger
     */
    Level level() const;
    
    /*!
     * @brief Sets the Level
     *
     * Call this to set the \ref Level of the \ref Logger.  This level can be inherited see
     * \ref Inheritance for more information.
     *
     * @param lev The \ref Level for the Logger.
     */
    void setLevel(const Level &lev);
    
protected:
    /*!
     * Logger constructor
     *
     * The Logger constructor is never used directly.  It is constructed by using
     * the accessor functions like \ref logger() and \ref rootLogger().
     */
    Logger();
    
private:
    LoggerPtr createLoggers(const std::string &loggerName);
    LoggerPtr createLogger(LoggerPtr parent, const std::string &baseName);
    void setName(const std::string &loggerName, const std::string &baseName);
    LoggerPtr findParent(const std::string &loggerName);
    
private:
    static LoggerPtr rootLogger_;
    static LoggerMap allNamedLoggers_;
    std::string baseName_;
    std::string fullName_;
    LoggerList children_;
    LoggerPtr parent_;
    Level level_;
};
    
} // sharklog

#endif // Logger_H
