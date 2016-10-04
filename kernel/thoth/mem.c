#include "thoth/mem.h"
#include "libc/stdio.h"

bool thoth_dmem_enabled = false;

void*	thoth_dmem_start = NULL;
size_t	thoth_dmem_size = 0;
void*	thoth_dmap_start = NULL;
size_t	thoth_dmap_size = 0;
void*	thoth_ddump_start = NULL;
size_t	thoth_ddump_size = 0;

size_t	thoth_dblock_size = 0;
size_t	thoth_dblock_count = 0;

const size_t thoth_dmap_entry_size = 1;

static size_t thoth_dmem_find_free_blocks(size_t blocks);

int thoth_mem_init(void* ptr, size_t size, size_t block_size)
{
	if (thoth_dmem_enabled)
		return 1;

	thoth_dmem_start = ptr;
	thoth_dmem_size = size;

	thoth_dblock_size = block_size;
	thoth_dblock_count = size / (thoth_dblock_size + thoth_dmap_entry_size);

	thoth_dmap_start = thoth_dmem_start;
	thoth_dmap_size = thoth_dblock_count * thoth_dmap_entry_size;

	thoth_ddump_start = (void*)((size_t)thoth_dmem_start + thoth_dmap_size);
	thoth_ddump_size = thoth_dblock_size * thoth_dblock_count;

	if (thoth_dblock_count <= 0)
		return 1;

	// Clear the memory region
	for (size_t i = 0; i < thoth_dblock_count; i ++)
	{
		((uint8_t*)thoth_dmap_start)[i] = (!USED) | (!HEAD);

		for (size_t j = 0; j < thoth_dblock_size; j ++)
			((uint8_t*)thoth_ddump_start + i * thoth_dblock_size)[j] = 0x0;
	}

	thoth_dmem_enabled = true;

	return 0;
}

static size_t thoth_dmem_find_free_blocks(size_t blocks)
{
	if (!thoth_dmem_enabled)
	{
		puts("$F4Error [FindFreeBlocks]$FF : Thoth dynamic memory is not enabled\n");
		return 0;
	}

	size_t last = 0;
	bool reset = false;
	for (size_t i = 0; i < thoth_dblock_count; i ++)
	{
		if (((uint8_t*)thoth_dmap_start)[i] & USED)
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

	return thoth_dblock_count;
}

void* thoth_mem_copy(const char* src, char* dest, size_t n)
{
	if (!thoth_dmem_enabled)
	{
		puts("$F4Error [Copy]$FF : Thoth dynamic memory is not enabled\n");
		return NULL;
	}

	for (size_t i = 0; i < n; i ++)
		dest[i] = src[i];
	return dest;
}

void* thoth_mem_allocate(size_t n)
{
	if (!thoth_dmem_enabled)
	{
		puts("$F4Error [Allocate]$FF : Thoth dynamic memory is not enabled\n");
		return NULL;
	}

	size_t block_number = (n - 1) / thoth_dblock_size + 1;
	size_t free_index = thoth_dmem_find_free_blocks(block_number);

	if (free_index >= thoth_dblock_count)
		return NULL;

	((uint8_t*)thoth_dmap_start)[free_index] = USED | HEAD;
	for (size_t i = 1; i < block_number; i ++)
		((uint8_t*)thoth_dmap_start)[free_index + i] = USED | (!HEAD);

	return (void*)((size_t)thoth_ddump_start + free_index * thoth_dblock_size);
}

int thoth_mem_free(const void* mem)
{
	if (!thoth_dmem_enabled)
	{
		puts("$F4Error [Free]$FF : Thoth memory map is not enabled\n");
		return 1;
	}

	size_t index = ((size_t)mem - (size_t)thoth_ddump_start);

	if (index % thoth_dblock_size != 0)
		return 1;

	index /= thoth_dblock_size;

	((uint8_t*)thoth_dmap_start)[index] = (!USED) | (!HEAD);
	for (size_t i = index + 1; i < thoth_dblock_count; i ++)
	{
		if (((uint8_t*)thoth_dmap_start)[i] & USED)
		{
			if (((uint8_t*)thoth_dmap_start)[i] & HEAD)
				break;
			else
				((uint8_t*)thoth_dmap_start)[i] = (!USED) | (!HEAD);
		}
		else
			break;
	}

	return 0;
}

void thoth_mem_display(size_t n)
{
	if (!thoth_dmem_enabled)
	{
		puts("$F4Error [Display]$FF : Thoth dynamic memory is not enabled\n");
		return;
	}

	for (size_t i = 0; i < n; i ++)
	{
		if (((uint8_t*)thoth_dmap_start)[i] & USED)
		{
			if (((uint8_t*)thoth_dmap_start)[i] & HEAD)
				puts("$B2H$B0");
			else
				puts("$B3T$B0");
		}
		else
		{
			puts("$B0-$B0");
		}
	}

	putchar('\n');
}
