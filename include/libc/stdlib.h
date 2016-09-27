#ifndef THOTH_LIBC_STDLIB
#define THOTH_LIBC_STDLIB

#include "stddef.h"

// String Conversion
int atoi(const char* str);
char* itoa(int value, char* str, int base);

// Pseudo-Random Sequence Generation
int rand();
void srand(unsigned int seed);

// Dynamic Memory Management
void* calloc(size_t num, size_t size);
void* malloc(size_t size);
void free(void* ptr);
void* realloc(void* ptr, size_t size);

// Integer Arithmetics
int abs(int n);

#endif
