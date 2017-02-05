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

#ifndef PROJECT_UTILFUNCTIONS_H
#define PROJECT_UTILFUNCTIONS_H

#include <vector>
#include <string>

namespace sharklog
{
    
/*!
 * @brief Utility Functions
 *
 * This class covers utility functions needed by the sharklog library.
 *
 * It is meant to be internal for the most part however they are available for
 * your use if you need them.
 *
 */
class UtilFunctions
{
public:
    /*!
     * @brief Split a string by delimiter
     *
     * This is a support function to split a string by delimiter since C++'s string
     * doesn't have that built in.
     *
     * It will return a vector of all the tokenized strings (in order).  So something like
     * *com.ambershark.sharklog* split by '.' would split into 3 strings:
     *
     * 1. com
     * 2. ambershark
     * 3. sharklog
     *
     * @param toSplit the string to split
     * @param delim the delimiter to use to split the string
     * @param discardEmptyTokens true to discard empty tokens, false to add them to the vector
     * @return A vector of strings with all the tokens
     */
    static std::vector<std::string> split(const std::string &toSplit, char delim, bool discardEmptyTokens=true);
    
    /*!
     * @brief Strip the last token off a string
     *
     * This is a support function to strip a token based on a delimited (\a delim) off
     * a string.
     *
     * For example if you pass x.y.z (delim is .) you would get back x.y from the function.
     *
     * If a delimiter is not found the whole entry string is returned.
     *
     * @param s string to take a token off
     * @param delim the delimiter to split the string with
     * @return A string without the final token
     */
    static std::string stripLastToken(const std::string &s, char delim);
};

} // sharklog

#endif //PROJECT_UTILFUNCTIONS_H
