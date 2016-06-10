#include "cstd/mem.h"

enum dyn_entry_state
{
	USED	= 1,
	HEAD	= 2,
};

bool dyn_enabled = false;

void*	dyn_mem_start = NULL;
size_t	dyn_mem_size = 0;
void*	dyn_map_start = NULL;
size_t	dyn_map_size = 0;
void*	dyn_dump_start = NULL;
size_t	dyn_dump_size = 0;

size_t	dyn_block_size = 0;
size_t	dyn_block_count = 0;

const size_t map_entry_size = 1;

void* cstd_mem_copy(const char* src, char* dest, size_t n)
{
	for (size_t i = 0; i < n; i ++)
		dest[i] = src[i];
	return dest;
}

int cstd_mem_init(void* ptr, size_t size, size_t block_size)
{
	dyn_mem_start = ptr;
	dyn_mem_size = size;

	dyn_block_size = block_size;
	dyn_block_count = size / (dyn_block_size + map_entry_size);

	dyn_map_start = dyn_mem_start;
	dyn_map_size = dyn_block_count * map_entry_size;

	dyn_dump_start = dyn_mem_start + dyn_map_size;
	dyn_dump_size = dyn_block_size * dyn_block_count;

	if (dyn_block_count <= 0)
		return 1;

	// Clear the memory region
	for (size_t i = 0; i < dyn_block_count; i ++)
	{
		((uint8_t*)dyn_map_start)[i] = !USED | !HEAD;

		for (size_t j = 0; j < dyn_block_size; j ++)
			((uint8_t*)dyn_dump_start + i * dyn_block_size)[j] = 0x0;
	}

	dyn_enabled = true;

	return 0;
}
