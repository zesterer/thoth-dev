#ifndef THOTH_KERNEL_CSTD_MEM
#define THOTH_KERNEL_CSTD_MEM

#include "cstd/com.h"

enum dyn_entry_state
{
	USED	= 1,
	HEAD	= 2,
};

extern bool dyn_enabled;

extern void*	dyn_mem_start;
extern size_t	dyn_mem_size;
extern void*	dyn_map_start;
extern size_t	dyn_map_size;
extern void*	dyn_dump_start;
extern size_t	dyn_dump_size;

extern size_t	dyn_block_size;
extern size_t	dyn_block_count;

extern const size_t map_entry_size;

void*	cstd_mem_copy(const char* src, char* dest, size_t n);
void*	cstd_mem_allocate(size_t n);
int		cstd_mem_free(const void* mem);

#endif
