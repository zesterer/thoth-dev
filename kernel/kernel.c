#include "cstd/mem.h"
#include "cstd/io.h"
#include "cstd/thoth.h"

#include "libc/stdio.h"

#include "thoth/util.h"

#if defined(THOTH_ARCH_i686) || defined(THOTH_ARCH_x86_64)
	#include "thoth/vga.h"
#endif

extern void* kernel_end asm("_kernel_end");

void kernel_early()
{

	#if defined(THOTH_ARCH_i686) || defined(THOTH_ARCH_x86_64)
		int status = thoth_vga_init();
	#endif

	putscheck("Entered kernel bootstrap", STATUS_SUCCESS);

	#if defined(THOTH_ARCH_x86_64)
		putscheck("Created temporary GDT", STATUS_SUCCESS);
		putscheck("Jumped to 64-bit mode", STATUS_SUCCESS);
	#endif

	#if defined(THOTH_ARCH_i686) || defined(THOTH_ARCH_x86_64)
		putscheck("Initialized VGA terminal", !(status == 0));
	#endif
}

void kernel_main()
{
	int status = thoth_dmem_init((void*)0x400000, 0x100000, 1024); // At 4 MB, 1 MB in size, composed of blocks of 1 KB
	putscheck("Initiated kernel dynamic memory", !(status == 0));

	putscheck("Boot sequence complete", STATUS_INFO);

	printf("\n$B8 Welcome to Thoth $B0\n");

	// Print version
	printf("$B8 Version:$B0 $F3");
	printf(THOTH_VERSION);
	printf("$FF\n");

	// Print arch
	printf("$B8 Arch   :$B0 $F3");
	printf(THOTH_ARCH);
	printf("$FF\n");

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
	cstd_str_copy("Hello, World! This is a memory-managed string!\n", msg);
	thoth_dmem_display(32);
	printf(msg);
}
