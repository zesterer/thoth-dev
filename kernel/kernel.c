#include "libc/stdlib.h"
#include "libc/stdio.h"
#include "libc/string.h"

#include "thoth/time.h"
#include "thoth/io.h"
#include "thoth/mem.h"

#if defined(THOTH_ARCH_i686) || defined(THOTH_ARCH_x86_64)
	#include "thoth/vga.h"
#endif

extern void* kernel_end asm("_kernel_end");

void kernel_early()
{
	#if defined(THOTH_ARCH_i686) || defined(THOTH_ARCH_x86_64)
		int status = thoth_vga_init();
	#endif

	thoth_io_check("Entered kernel bootstrap", STATUS_SUCCESS);

	#if defined(THOTH_ARCH_x86_64)
		thoth_io_check("Created temporary GDT", STATUS_SUCCESS);
		thoth_io_check("Jumped to 64-bit mode", STATUS_SUCCESS);
	#endif

	#if defined(THOTH_ARCH_i686) || defined(THOTH_ARCH_x86_64)
		thoth_io_check("Initialized VGA terminal", !(status == 0));
	#endif
}

void kernel_welcome()
{
	// Print welcome message
	printf("\n$B8Welcome to Thoth $B0\n");

	// Print version
	printf("$B8Version:$B0$F3 ");
	printf(THOTH_VERSION);
	printf("$FF\n");

	// Print arch
	printf("$B8Arch   :$B0$F3 ");
	printf(THOTH_ARCH);
	printf("$FF\n");
}

void kernel_main()
{
	thoth_io_check("Entered kernel main", STATUS_SUCCESS);

	int status = thoth_mem_init((void*)0x1000000, 0x100000, 1024); // At 16 MB, 1 MB in size, composed of blocks of 1 KB
	thoth_io_check("Initiated kernel dynamic memory", !(status == 0));

	thoth_io_check("Boot sequence complete", STATUS_INFO);

	kernel_welcome();

	// Dynamic memory test
	{
		thoth_mem_display(32);
		void* a = malloc(3);
		thoth_mem_display(32);
		void* b = malloc(4000);
		thoth_mem_display(32);
		void* c = malloc(3);
		thoth_mem_display(32);
		void* d = malloc(2100);
		thoth_mem_display(32);

		free(a);
		thoth_mem_display(32);
		free(b);
		thoth_mem_display(32);
		free(c);
		thoth_mem_display(32);
		free(d);
		thoth_mem_display(32);

		char* msg = malloc(1024);
		strcpy("Hello, World! This is a memory-managed string!\n", msg);
		thoth_mem_display(32);
		printf(msg);
	}

	// CPU cycle clock
	while (false)
	{
		if (rdtsc() % 10000000 == 0)
			printf("Tick!\n");
	}
}
