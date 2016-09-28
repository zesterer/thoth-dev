/*
* 	filename	: data.h
* 	component	: libc
* 	description	: Date type definitions
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
#ifndef _THOTH_COM_TYPE_DATA_H
#define _THOTH_COM_TYPE_DATA_H 1

/* GCC STD */

#include "stdint.h"

// C++ Compatibility
#ifdef __cplusplus
extern "C" {
#endif

/* Data Types */

typedef uint8_t		byte;	// A byte (8 bits)
typedef uint16_t	word;	// A word (16 bits, 2 bytes)

/* Pointer Types */

typedef void*		ptr;	// A generic pointer to a memory location

/* Size Types */

typedef size_t		psize;	// A generic memory size integer

// C++ Compatibility
#ifdef __cplusplus
} //extern "C"
#endif

#endif //#ifndef _THOTH_COM_TYPE_DATA_H
