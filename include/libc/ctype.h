/*
* 	filename	: ctype.h
* 	component	: libc
* 	description	: Character handling functions
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

#ifndef _CTYPE_H
#define _CTYPE_H 1

/* C++ Compatibility */

#ifdef __cplusplus
extern "C" {
#endif

/* Character Classification Functions */

int isalnum(int c);
int isblank(int c);
int isalpha(int c);
int iscntrl(int c);
int isdigit(int c);
int isgraph(int c);
int islower(int c);
int isprint(int c);
int ispunct(int c);
int isspace(int c);
int isupper(int c);
int isxdigit(int c);

/* Character Conversion Functions */

int toupper(int c);
int tolower(int c);

#ifdef __cplusplus
} //extern "C"
#endif

#endif
