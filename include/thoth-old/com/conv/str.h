/*
* 	filename	: str.h
* 	component	: thoth
* 	description	: String conversion function definitions
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
#ifndef _THOTH_COM_CONV_STR_H
#define _THOTH_COM_CONV_STR_H 1

/* THOTH */

#include "thoth/com/type/all.h"

/* GCC STD */

#include "stdarg.h"

// C++ Compatibility
#ifdef __cplusplus
extern "C" {
#endif

/* String to integer Conversion Functions */

ui8		tc_StrToUint8(str s);
ui16	tc_StrToUInt16(str s);
ui32	tc_StrToUInt32(str s);
ui64	tc_StrToUInt64(str s);

str		tc_StrToInt8(i8 x);
str		tc_StrToInt16(i16 x);
str		tc_StrToInt32(i32 x);
str		tc_StrToInt64(i64 x);

str		tc_StrToInt(intg x);

/* String to floating-point Conversion Functions */

f32		tc_StrToFloat32(str s);
f64		tc_StrToFloat64(str s);

/* String to boolean Conversion Functions */

bool	tc_StrToBool(str s);

// C++ Compatibility
#ifdef __cplusplus
} //extern "C"
#endif

#endif //#ifndef _THOTH_COM_CONV_STR_H
