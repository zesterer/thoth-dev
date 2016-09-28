/*
* 	filename	: int.h
* 	component	: libc
* 	description	: Integer type definitions
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
#ifndef _THOTH_COM_TYPE_INT_H
#define _THOTH_COM_TYPE_INT_H 1

/* GCC STD */

#include "stdint.h"

// C++ Compatibility
#ifdef __cplusplus
extern "C" {
#endif

/* Unsigned Integer Types */

typedef uint8_t			ui8;	// 8-bit unsigned integer
typedef uint16_t		ui16;	// 16-bit unsigned integer
typedef uint32_t		ui32;	// 32-bit unsigned integer
typedef uint64_t		ui64;	// 64-bit unsigned integer

typedef unsigned int	uintg;	// generic size unsigned integer

/* Signed Integer Types */

typedef int8_t			i8;		// 8-bit signed integer
typedef int16_t			i16;	// 16-bit signed integer
typedef int32_t			i32;	// 32-bit signed integer
typedef int64_t			i64;	// 64-bit signed integer

typedef signed int		intg;	// generic size signed integer

// C++ Compatibility
#ifdef __cplusplus
} //extern "C"
#endif

#endif //#ifndef _THOTH_COM_TYPE_INT_H
