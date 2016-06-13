#include "cstd/mem.h"
#include "cstd/io.h"

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

size_t cstd_mem_find_free_blocks(size_t blocks)
{
	size_t last = 0;
	bool reset = false;
	for (size_t i = 0; i < dyn_block_count; i ++)
	{
		if (((uint8_t*)dyn_map_start)[i] & USED)
		{
			reset = true;
			last = i;
		}
		else if (i - last >= blocks && !reset)
			return last;
		else
		{
			if (reset)
			{
				last = i;
				reset = false;
			}
		}
	}

	return dyn_block_count;
}

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
		((uint8_t*)dyn_map_start)[i] = (!USED) | (!HEAD);

		for (size_t j = 0; j < dyn_block_size; j ++)
			((uint8_t*)dyn_dump_start + i * dyn_block_size)[j] = 0x0;
	}

	dyn_enabled = true;

	return 0;
}

void* cstd_mem_allocate(size_t n)
{
	size_t block_number = (n - 1) / dyn_block_size + 1;
	size_t free_index = cstd_mem_find_free_blocks(block_number);

	if (free_index >= dyn_block_count)
		return NULL;

	((uint8_t*)dyn_map_start)[free_index] = USED | HEAD;
	for (size_t i = 1; i < block_number; i ++)
		((uint8_t*)dyn_map_start)[free_index + i] = USED | (!HEAD);

	return dyn_dump_start + free_index * dyn_block_size;
}

int cstd_mem_free(const void* mem)
{
	size_t index = (mem - dyn_dump_start);

	if (index % dyn_block_size != 0)
		return 1;

	index /= dyn_block_size;

	((uint8_t*)dyn_map_start)[index] = (!USED) | (!HEAD);
	for (size_t i = index + 1; i < dyn_block_count; i ++)
	{
		if (((uint8_t*)dyn_map_start)[i] & USED)
		{
			if (((uint8_t*)dyn_map_start)[i] & HEAD)
				break;
			else
				((uint8_t*)dyn_map_start)[i] = (!USED) | (!HEAD);
		}
		else
			break;
	}

	return 0;
}

void cstd_mem_display(size_t n)
{
	for (size_t i = 0; i < n; i ++)
	{
		if (((uint8_t*)dyn_map_start)[i] & USED)
		{
			if (((uint8_t*)dyn_map_start)[i] & HEAD)
				cstd_io_print("$B2H$B0");
			else
				cstd_io_print("$B3T$B0");
		}
		else
		{
			cstd_io_print("$B0-$B0");
		}
	}

	cstd_io_put('\n');
}
