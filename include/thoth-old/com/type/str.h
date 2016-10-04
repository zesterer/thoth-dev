/*
* 	filename	: str.h
* 	component	: thoth
* 	description	: String type definitions
*
* 	This file is part of Thoth.
*
* 	Thoth is free software: you can redistribute it and/or modify
* 	it under the terms of the GNU General Public License as published by
* 	the Free Software Foundation, either version 3 of the License, or
* 	(at your option) any later version.
*
* 	Thoth is distributed in the hope that it will be useful,
* 	but WITHOUT ANY WARRANTY; without even the implied warranty of
* 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* 	GNU General Public License for more details.
*
* 	You should have received a copy of the GNU General Public License
* 	along with Thoth.  If not, see <http://www.gnu.org/licenses/>.
*/

// Header Guard
#ifndef _THOTH_COM_TYPE_STR_H
#define _THOTH_COM_TYPE_STR_H 1

/* THOTH */

#include "thoth/com/type/data.h"

// C++ Compatibility
#ifdef __cplusplus
extern "C" {
#endif

/* Character Types */

typedef uint32	wchar;

/* String Types */

typedef char*	cstr;												// C-style string
typedef struct TC_STR { char* ptr; psize len; } str;				// Thoth-style pool-allocated length-defined string
typedef struct TC_WSTR { wchar* ptr; psize len; } wstr;				// wide Thoth-style pool-allocated length-defined string

// C++ Compatibility
#ifdef __cplusplus
} //extern "C"
#endif

#endif //#ifndef _THOTH_COM_TYPE_STR_H
