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

#include <string>
#include <memory>
#include <list>
#include <vector>
#include <sstream>

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
     * \brief Checks if this logger is the root logger
     *
     * @return True if this is the root logger, false if not.
     */
    bool isRoot() const;
    
    /*!
     * \brief Gets the name of the logger
     *
     * Returns the name of this logger.  Name will be blank if it is the root logger.
     * No other loggers can be created with a blank name.
     * You can test if it's the root logger with \ref isRoot().
     *
     * @return The name of this logger.
     * \sa logger()
     */
    std::string name() const;
    
    /*!
     * \brief Gets the parent Logger
     *
     * If there is a parent logger (i.e. rootLogger() does not have one), then the parent
     * Logger is returned.
     *
     * @return A pointer to the parent logger.
     */
    LoggerPtr parent() const;
    
protected:
    /*!
     * Logger constructor
     *
     * The Logger constructor is never used directly.  It is constructed by using
     * the accessor functions like \ref logger() and \ref rootLogger().
     */
    Logger();
    
private:
    bool hasChild(const std::string &name) const;
    bool hasChild(std::vector<std::string> *tokens) const;
    
private:
    static LoggerPtr rootLogger_;
    std::string name_;
    LoggerList children_;
    LoggerPtr parent_;
};
    
} // sharklog

#endif // Logger_H
