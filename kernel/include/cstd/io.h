#ifndef THOTH_KERNEL_CSTD_IO
#define THOTH_KERNEL_CSTD_IO

#include "cstd/com.h"

void cstd_io_put(char c);
void cstd_io_print(const char* str);
void cstd_io_printn(const char* str, size_t len);

#endif
