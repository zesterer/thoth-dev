/*
* 	filename	: stdlib.h
* 	component	: libc
* 	description	: C Standard General Utilities Library
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

#ifndef _STRING_H
#define _STRING_H 1

/* GCC STD */

#include "stddef.h"
#include "stdint.h"

/* Header Fragments (prevent namespace pollution) */

#include "libc/fragment/_null_value.h"

/* C++ Compatibility */

#ifdef __cplusplus
extern "C" {
#endif

/* Types */

typedef size_t size_t;

/* Copying */

void*	memcpy(void* destination, const void* source, size_t num);
void*	memmove(void* destination, const void* source, size_t num);
char*	strcpy(char* destination, const char* source);
char*	strncpy(char* destination, const char* source, size_t num);

/* Concatenation */

char*	strcat(char* destination, const char* source);
char*	strncat(char* destination, const char* source, size_t num);

/* Comparasion */

int		memcmp(const void* ptr1, const void* ptr2, size_t num);
int		strcmp(const char* str1, const char* str2);
int		strcoll(const char* str1, const char* str2);
int		strncmp(const char* str1, const char* str2, size_t num);
size_t	strxfrm(char* destination, const char* source, size_t num);

/* Searching */

void*	memchr(void* ptr, int value, size_t num);

/* Other */

void*	memset(void* ptr, int value, size_t num);
char*	strerror(int errnum);
size_t	strlen(const char* str);

#ifdef __cplusplus
} //extern "C"
#endif

#endif
