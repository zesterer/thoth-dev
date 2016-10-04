/*
* 	filename	: mem.h
* 	component	: thoth
* 	description	: Memory-related function definitions
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
#ifndef _THOTH_COM_MEM_MEM_H
#define _THOTH_COM_MEM_MEM_H 1

/* THOTH */

#include "thoth/com/type/all.h"

/* GCC STD */

#include "stdarg.h"

// C++ Compatibility
#ifdef __cplusplus
extern "C" {
#endif

/* Global Memory Pool Functions */

ptr		tc_Allocate(psize n);
sint	tc_Deallocate(ptr p);

// C++ Compatibility
#ifdef __cplusplus
} //extern "C"
#endif

#endif //#ifndef _THOTH_COM_MEM_MEM_H
