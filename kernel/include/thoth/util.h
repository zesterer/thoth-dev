#ifndef THOTH_KERNEL_THOTH_UTIL
#define THOTH_KERNEL_THOTH_UTIL

#include "cstd/com.h"

int thoth_dmem_init(void* ptr, size_t size, size_t block_size);
void thoth_dmem_display(size_t n);

#endif
