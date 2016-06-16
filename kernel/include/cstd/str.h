#ifndef THOTH_KERNEL_CSTD_STR
#define THOTH_KERNEL_CSTD_STR

#include "cstd/com.h"

size_t		cstd_str_length(const char* str);
char*		cstd_str_copy(const char* src, char* dest);
char*		cstd_str_copy_n(const char* src, char* dest, size_t n);
const char*	cstd_str_find(const char* str, char val);

#endif
