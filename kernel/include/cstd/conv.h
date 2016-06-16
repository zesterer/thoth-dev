#ifndef THOTH_KERNEL_CSTD_CONV
#define THOTH_KERNEL_CSTD_CONV

#include "cstd/com.h"

int cstd_conv_str_to_int(const char* str);
char* cstd_conv_int_to_str(int value, char* str, int base);

#endif
