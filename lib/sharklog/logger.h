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
#include <sharklog/outputter.h>
#include <sharklog/layout.h>
#include <sharklog/location.h>
#include <string>
#include <memory>
#include <list>
#include <vector>
#include <sstream>
#include <map>
#include <mutex>
#include <string.h>

/*!
 * The main namespace of the SharkLog project.
 *
 * Everything will be protected by this namespace.
 */
namespace sharklog
{
    
class Logger;
class Layout;
    
/*!
 * \var LoggerPtr
 *
 * A pointer to a \ref Logger instance.
 */
using LoggerPtr = std::shared_ptr<Logger>;
    
/*!
 * \brief Logger instance
 *
 * This class covers the logger creation and interface into the sharklog system.
 *
 * The Logger instances are created as singleton objects.  Using new or instantiating
 * the logger without using the interface will not work.  It will throw a compilation
 * error.  You will need to use \ref Logger::rootLoot() and \ref Logger::logger() to
 * get instances of Loggers.
 *
 * There will always be a root logger.  Any call into the Logger system will create
 * this logger if it does not already exist.
 *
 * The Logger needs to be configured to be used.  For this release there is no
 * automatic configuration class.  In fact configuration is severly limited for this
 * 0.1 release.  Currently the only supported configuration will be with
 * \ref ConsoleOutputter and \ref StandardLayout.
 *
 * The default level on the root logger is \ref Level::all().  You can change this with
 * \ref setLevel().  See \ref Inheritance for more information on levels for loggers
 * inherited from the root.
 *
 * \code
 * #include <sharklog/standardlayout.h>
 * #include <sharklog/consoleoutputter.h>
 * #include <sharklog/logger.h>
 *
 * int main()
 * {
 *    // set up logger
 *    auto root = Logger::rootLogger();
 *    root->setLayout(LayoutPtr(new StandardLayout()));
 *    root->addOutputter(OutputterPtr(new ConsoleOutputter()));
 *
 *    // log a message to root
 *    root->log(Level::trace(), "Hello");
 *
 *    // log a message to a new name logger that inherits from root
 *    Logger::logger("test")->log(Level::info(), "World");
 * }
 * \endcode
 */
class Logger
{
    // custom case insensitive string compare
    struct caseInsensitiveCompare : public std::binary_function<std::string, std::string, bool>
    {
        bool operator()(const std::string &lhs, const std::string &rhs) const
        {
            return strcasecmp(lhs.c_str(), rhs.c_str()) < 0;
        }
    };
    
    using LoggerList = std::list<LoggerPtr>;
    using LoggerMap = std::map<std::string, LoggerPtr, caseInsensitiveCompare>;
    
public:
	using OutputterList = std::list<OutputterPtr>;

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
    
    /*!
     * @brief Gets the layout
     *
     * Returns a LayoutPtr to the current layout for this Logger.
     *
     * @return the current layout
     */
    LayoutPtr layout() const;
    
    /*!
     * @brief Sets the layout
     *
     * Set the \ref Layout for this logger.
     *
     * For example:
     *
     * \code
     * Logger::rootLogger()->setLayout(LayoutPtr(new StandardLayout));
     * \endcode
     *
     * @param p the layout you want to set
     * \sa layout()
     */
    void setLayout(LayoutPtr p);
    
    /*!
     * @brief Checks if valid
     *
     * Checks if the Logger is valid.
     *
     * It is valid if it has a layout and outputter.
     *
     * @return true if valid, false if not
     * @sa setLayout(), addOutputter()
     */
    bool isValid() const;

	/*!
	 * @brief Adds an Outputter
	 *  
	 * Add an \ref Outputter to the Logger.  All Outputters will be sent the 
	 * log message when it is logged. 
	 *  
	 * \param op The Outputter to add
	 */
	void addOutputter(OutputterPtr op);

	/*!
	 * @brief Remove an Outputter 
	 *  
	 * Remove an \ref Outputter from the Logger. 
	 * 
	 * \param op The outputter to remove
	 */
	void removeOutputter(OutputterPtr op);

	/*!
	 * @brief List of Outputters 
	 *  
	 * Gets a list of all the Outputters that this Logger will use when a message 
	 * is logged. 
	 * 
	 * \return OutputterList List of current Outputters
	 */
	OutputterList outputters() const;
    
    /*!
     * @brief Log a message
     *
     * Logs a message \a msg.  This will use the \ref Layout and all the \a Outputter's that
     * are attached to this logger.
     *
     * You can call this function directly or you can use the macros \ref Macros.  You can also
     * use the streaming support class to log using a C++ stream.  See \ref LoggerStream.
     *
     * @param level The level to log this message with
     * @param msg the message string to log
     * @sa addOutputter(), setLayout(), LoggerStream
     * @returns true if logged, false if not
     */
    bool log(const Level &level, const std::string &msg, const Location &loc=Location()) const;
    
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
    LayoutPtr layout_;
	OutputterList outputters_;
	static std::recursive_mutex mutex_;
};
    
} // sharklog

//! \todo document these macros
#define SHARKLOG_DEBUG(logger, message) { \
    if (logger->level().hasDebug()) {\
        logger->log(Level::debug(), message, SHARKLOG_LOCATION); } \
    }

#define SHARKLOG_TRACE(logger, message) { \
    if (logger->level().hasTrace()) {\
        logger->log(Level::trace(), message, SHARKLOG_LOCATION); } \
    }

#define SHARKLOG_INFO(logger, message) { \
    if (logger->level().hasInfo()) {\
        logger->log(Level::info(), message, SHARKLOG_LOCATION); } \
    }

#define SHARKLOG_WARN(logger, message) { \
    if (logger->level().hasWarn()) {\
        logger->log(Level::warn(), message, SHARKLOG_LOCATION); } \
    }

#define SHARKLOG_ERROR(logger, message) { \
    if (logger->level().hasError()) {\
        logger->log(Level::error(), message, SHARKLOG_LOCATION); } \
    }

#define SHARKLOG_FATAL(logger, message) { \
    if (logger->level().hasFatal()) {\
        logger->log(Level::fatal(), message, SHARKLOG_LOCATION); } \
    }

#endif // Logger_H
