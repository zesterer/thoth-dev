#include "cstd/com.h"

void*	cstd_mem_copy(const char* src, char* dest, size_t n);

int		cstd_mem_init(void* ptr, size_t size, size_t block_size);
void*	cstd_mem_allocate(size_t n);
int		cstd_mem_free(const void* mem);
void	cstd_mem_display(size_t n);
