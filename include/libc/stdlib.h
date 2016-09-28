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

#ifndef _STDLIB_H
#define _STDLIB_H 1

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

typedef struct { int quot; int rem; } div_t;
typedef struct { long quot; long rem; } ldiv_t;
typedef struct { long long quot; long long rem; } lldiv_t;
typedef size_t size_t;

/* Macros */

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define MB_CUR_MAX 4
#define RAND_MAX 2147483647

/* String Conversion */

double			atof(const char* str);
int				atoi(const char* str);
long			atol(const char* str);
long long		atoll(const char* str);
double			strtod(const char* str, char** endptr);
float			strtof(const char* str, char** endptr);
long			strtol(const char* str, char** endptr, int base);
long double		strtold(const char* str, char** endptr, int base);
long long		strtoll(const char* str, char** endptr, int base);
unsigned long	strtoul(const char* str, char** endptr, int base);
unsigned long	long strtoull(const char* str, char** endptr, int base);

char*			itoa(int value, char* str, int base);

/* Pseudo-Random Sequence Generation */

int				rand();
void			srand(unsigned int seed);

/* Dynamic Memory Management */

void*			calloc(size_t num, size_t size);
void*			malloc(size_t size);
void			free(void* ptr);
void*			realloc(void* ptr, size_t size);

/* Environment */

void			abort();
int				atexit(void (*func)(void));
int				at_quick_exit(void (*func)(void));
void			exit(int status);
char*			getenv(const char* name);
void			quick_exit(int status);
int				system(const char* string);
void			_Exit(int status);

/* Searching And Sorting */

void*			bsearch(const void* key, const void* base, size_t nitems, size_t size, int (*compar)(const void*, const void*));
void			qsort(void* base, size_t nitems, size_t size, int (*compar)(const void*, const void*));

/* Integer Arithmetics */

int				abs(int n);
div_t			div(int number, int denom);
long			labs(long x);
ldiv_t			ldiv(long numer, long denom);
long long		llabs(long long x);
lldiv_t			lldiv(long long numer, long long denom);

/* Multibyte Characters */

int mblen(const char* str, size_t n);
int mbtowc(wchar_t* pwcs, const char* str, size_t n);
int wctomb(char* str, wchar_t wc);

/* Multibyte Strings */

size_t mbstowcs(uint8_t* pwcs, const char* str, size_t n);
size_t wcstombs(char* str, const uint8_t* pwcs, size_t n);

#ifdef __cplusplus
} //extern "C"
#endif

#endif
