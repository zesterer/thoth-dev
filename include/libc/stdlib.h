#ifndef THOTH_LIBC_STDLIB
#define THOTH_LIBC_STDLIB

#include "stddef.h"

//String conversion
int atoi(const char* str);
char* itoa(int value, char* str, int base);

//Pseudo-random sequence generation
int rand();
void srand(unsigned int seed);

//Integer arithmetics
int abs(int n);

#endif
