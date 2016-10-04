/*
* 	filename	: int.h
* 	component	: thoth
* 	description	: Integer conversion function definitions
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
#ifndef _THOTH_COM_CONV_INT_H
#define _THOTH_COM_CONV_INT_H 1

/* THOTH */

#include "thoth/com/type/all.h"

/* GCC STD */

#include "stdarg.h"

// C++ Compatibility
#ifdef __cplusplus
extern "C" {
#endif

/* Integer Conversion Functions */

str		tc_UInt8ToStr(ui8 x);
str		tc_UInt16ToStr(ui16 x);
str		tc_UInt32ToStr(ui32 x);
str		tc_UInt64ToStr(ui64 x);

str		tc_Int8ToStr(i8 x);
str		tc_Int16ToStr(i16 x);
str		tc_Int32ToStr(i32 x);
str		tc_Int64ToStr(i64 x);

str		tc_IntToStr(intg x);

// C++ Compatibility
#ifdef __cplusplus
} //extern "C"
#endif

#endif //#ifndef _THOTH_COM_CONV_INT_H
