#include "thoth/util.h"
#include "cstd/mem.h"

int thoth_dmem_init(void* ptr, size_t size, size_t block_size)
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

void thoth_dmem_display(size_t n)
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
