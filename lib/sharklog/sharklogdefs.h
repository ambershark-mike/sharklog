////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2017, by Ambershark, LLC.
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

#ifndef __sharklogdef_H
#define __sharklogdef_H

/*!
 * \file sharklogdefs.h
 *
 * This file has the definitions needed for OS compatibility as well as
 * anything else that needs to be global across the library.
 */

////////////////////////////////////////////////////////////
//
// Anything that is NOT visual studio
//
////////////////////////////////////////////////////////////

#if !defined(_MSC_VER) // NON Visual Studio
	#define SHARKLOGAPI
#endif // NOT _MSC_VER


////////////////////////////////////////////////////////////
//
// _MSC_VER - Visual Studio specific
//
////////////////////////////////////////////////////////////

#if defined(_MSC_VER) // Visual Studio in windows

#if defined(SHARKLOG_EXPORTS)
	#define SHARKLOGAPI __declspec(dllexport)
#else
	#define SHARKLOGAPI __declspec(dllimport)
#endif

#endif // _MSC_VER


////////////////////////////////////////////////////////////
//
// Windows 32 and 64 bit including visual studio and mingw
// cygwin, etc.
//
////////////////////////////////////////////////////////////

#if defined(_WIN32) || defined(_WIN64)

#if !defined(strcasecmp)
	#define strcasecmp _stricmp
#endif

#if !defined(localtime_r)
	#define localtime_r(a,b) localtime_s(b,a)
#endif

#endif // _WIN32 || _WIN64

#endif // sharklogdef_H
