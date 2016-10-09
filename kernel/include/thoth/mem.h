#ifndef THOTH_KERNEL_THOTH_MEM
#define THOTH_KERNEL_THOTH_MEM

#include "stddef.h"
#include "stdint.h"
#include "stdbool.h"

enum thoth_dmem_entry_state
{
	USED	= 1,
	HEAD	= 2,
};

extern bool thoth_dmem_enabled;

extern void*	thoth_dmem_start;
extern size_t	thoth_dmem_size;
extern void*	thoth_dmap_start;
extern size_t	thoth_dmap_size;
extern void*	thoth_ddump_start;
extern size_t	thoth_ddump_size;

extern size_t	thoth_dblock_size;
extern size_t	thoth_dblock_count;

extern const size_t thoth_dmap_entry_size;

int		thoth_mem_init(void* ptr, size_t size, size_t block_size);
void	thoth_mem_display(size_t n);

void*	thoth_mem_copy(const char* src, char* dest, size_t n);
void*	thoth_mem_allocate(size_t n);
void*	thoth_mem_reallocate(void* mem, size_t n);
int		thoth_mem_free(const void* mem);

#endif
