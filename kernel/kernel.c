#include "cstd/str.h"
#include "cstd/mem.h"
#include "cstd/io.h"
#include "cstd/thoth.h"

#include "thoth/util.h"
#include "thoth/vga.h"

extern void* kernel_end asm("_kernel_end");

void kernel_early()
{
	thoth_vga_init();

	putscheck("Entered kernel bootstrap", STATUS_SUCCESS);

	#if defined(THOTH_ARCH_x86_64)
		putscheck("Created temporary GDT", STATUS_SUCCESS);
		putscheck("Jumped to 64-bit mode", STATUS_SUCCESS);
	#endif

	putscheck("Initialized VGA terminal", STATUS_SUCCESS);
}

void kernel_main()
{
	int result = thoth_dmem_init((void*)0x400000, 0x100000, 1024); // At 4 MB, 1 MB in size, composed of blocks of 1 KB
	putscheck("Initiated kernel dynamic memory", !(result == 0));

	putscheck("Boot sequence complete", STATUS_INFO);

	cstd_io_print("\n$B8 Welcome to Thoth $B0\n");

	// Print version
	cstd_io_print("$B8 Version:$B0 $F3");
	cstd_io_print(THOTH_VERSION);
	cstd_io_print("$FF\n");

	// Print arch
	cstd_io_print("$B8 Arch   :$B0 $F3");
	cstd_io_print(THOTH_ARCH);
	cstd_io_print("$FF\n");

	thoth_dmem_display(32);
	void* a = cstd_mem_allocate(3);
	thoth_dmem_display(32);
	void* b = cstd_mem_allocate(4000);
	thoth_dmem_display(32);
	void* c = cstd_mem_allocate(3);
	thoth_dmem_display(32);
	void* d = cstd_mem_allocate(2100);
	thoth_dmem_display(32);

	cstd_mem_free(a);
	thoth_dmem_display(32);
	cstd_mem_free(b);
	thoth_dmem_display(32);
	cstd_mem_free(c);
	thoth_dmem_display(32);
	cstd_mem_free(d);
	thoth_dmem_display(32);

	char* msg = cstd_mem_allocate(1024);
	cstd_str_copy("Hello, this is a memory-managed string!\n", msg);
	thoth_dmem_display(32);
	cstd_io_print(msg);
}
