#ifndef THOTH_LIBC_STDLIB
#define THOTH_LIBC_STDLIB

#include "stddef.h"

//String conversion
int atoi(const char* str);
char* itoa(int value, char* str, int base);

#endif
