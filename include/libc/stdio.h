#ifndef THOTH_LIBC_STDIO
#define THOTH_LIBC_STDIO

#include "stddef.h"
#include "stdint.h"
#include "stdarg.h"

// A temporary FILE typedef
typedef uint32_t FILE;

// Operations on files

int		remove(const char* filename);
int		rename(const char* oldname, const char* newname);
FILE*	tmpfile();
char*	tmpnam(char* str);

// File access

int		fclose(FILE* stream);
int		fflush(FILE* stream);
FILE*	fopen(const char* filename, const char* mode);
FILE*	freopen(const char* filename, const char* mode, FILE* stream);
void	setbuf(FILE* stream, char* buffer);
int		setvbuf(FILE* stream, char* buffer, int mode, size_t size);

// Formatted input/output

int fprintf(FILE* stream, const char* format, ...);
int fscanf(FILE* stream, const char* format, ...);
int printf(const char* format, ...);
int scanf(const char* format, ...);
int snprintf(char* s, size_t n, const char* format, ...);
int sprintf(char* str, const char* format, ...);
int sscanf(const char* s, const char* format, ...);
int vfprintf(FILE* stream, const char* format, va_list arg);
int vfscanf(FILE* stream, const char* format, va_list arg);
int vprintf(const char* format, va_list arg);
int vscanf(const char* format, va_list arg);
int vsnprintf(char* s, size_t n, const char* format, va_list arg);
int vsprintf(char* s, const char* format, va_list arg);
int vsscanf(const char* s, const char* format, va_list arg);

// Character input/output

int putchar(int character);
int puts(const char* str);

#endif
