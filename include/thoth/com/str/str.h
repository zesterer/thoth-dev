/*
* 	filename	: str.h
* 	component	: libc
* 	description	: String-related function definitions
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
#ifndef _THOTH_COM_STR_STR_H
#define _THOTH_COM_STR_STR_H 1

/* THOTH */

#include "thoth/com/type/all.h"

/* GCC STD */

#include "stdarg.h"

// C++ Compatibility
#ifdef __cplusplus
extern "C" {
#endif

// NOTE: most functions in this file require the existence of a dynamic memory pool

/* String Creation Functions */

str		tc_Str(const cstr s);

/* String Attribute Functions */

ptr		tc_StrSrc(str s);
psize	tc_StrLen(str s);

/* String Access Functions */

char	tc_StrAt(str s, psize pos);

/* String Manipulation Functions */

str		tc_CopyStr(str s);
str		tc_Concat(str s, ...);
str		tc_SubStr(str s, psize offset, psize len);

/* String Search Functions */

psize	tc_StrFindFirst(str s, char c);
psize	tc_StrFindLast(str s, char c);
psize	tc_StrFindSubStr(str s, str sub);

// C++ Compatibility
#ifdef __cplusplus
} //extern "C"
#endif

#endif //#ifndef _THOTH_COM_STR_STR_H
