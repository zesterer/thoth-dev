/*
* 	filename	: stdio.h
* 	component	: libc
* 	description	: C library to perform Input/Output operations
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

#ifndef _STDIO_H
#define _STDIO_H 1

/* GCC STD */

#include "stddef.h"
#include "stdint.h"
#include "stdarg.h"

/* Header Fragments (prevent namespace pollution) */

#include "libc/fragment/_file_type.h"
#include "libc/fragment/_null_value.h"

/* C++ Compatibility */

#ifdef __cplusplus
extern "C" {
#endif

/* Types */

typedef _file_handle FILE;
typedef size_t fpos_t;

/* Macros */

#define BUFSIZ 512
#define EOF -1
#define FILENAME_MAX 255
#define FOPEN_MAX 8
#define L_tmpnam 8
#define TMP_MAX 8

/* Operations On Files */

int		remove(const char* filename);
int		rename(const char* oldname, const char* newname);
FILE*	tmpfile();
char*	tmpnam(char* str);

// File Access */

int		fclose(FILE* stream);
int		fflush(FILE* stream);
FILE*	fopen(const char* filename, const char* mode);
FILE*	freopen(const char* filename, const char* mode, FILE* stream);
void	setbuf(FILE* stream, char* buffer);
int		setvbuf(FILE* stream, char* buffer, int mode, size_t size);

/* Formatted Input/Output */

int		fprintf(FILE* stream, const char* format, ...);
int		fscanf(FILE* stream, const char* format, ...);
int		printf(const char* format, ...);
int		scanf(const char* format, ...);
int		snprintf(char* s, size_t n, const char* format, ...);
int		sprintf(char* str, const char* format, ...);
int		sscanf(const char* s, const char* format, ...);
int		vfprintf(FILE* stream, const char* format, va_list arg);
int		vfscanf(FILE* stream, const char* format, va_list arg);
int		vprintf(const char* format, va_list arg);
int		vscanf(const char* format, va_list arg);
int		vsnprintf(char* s, size_t n, const char* format, va_list arg);
int		vsprintf(char* s, const char* format, va_list arg);
int		vsscanf(const char* s, const char* format, va_list arg);

/* Character Input/Output */

int		fgetc(FILE* stream);
char*	fgets(char* str, int n, FILE* stream);
int		fputc(int c, FILE* stream);
int		fputs(const char* str, FILE* stream);
int		getc(FILE* stream);
int		getchar(void);
char*	gets(char* str);
int		putc(int c, FILE* stream);
int		putchar(int c);
int		puts(const char* str);
int		ungetc(int c, FILE* stream);

/* Direct Input/Output */

size_t	fread(void* ptr, size_t size, size_t nmemb, FILE* stream);
size_t	fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream);

/* File Positioning */

int		fgetpos(FILE* stream, fpos_t* pos);
int		fseek(FILE* stream, long offset, int origin);
int		fsetpos(FILE* stream, const fpos_t* pos);
long	ftell(FILE* stream);
void	rewind(FILE* stream);

/* Error Handling */

void	clearerr(FILE* stream);
int		feof(FILE* stream);
int		ferror(FILE* stream);
void	perror(const char* str);

#ifdef __cplusplus
} //extern "C"
#endif

#endif
