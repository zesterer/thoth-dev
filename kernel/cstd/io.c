#include "cstd/io.h"
#include "thoth/vga.h"

void cstd_io_put(char c)
{
	#if defined(THOTH_ARCH_i686)
		thoth_vga_putc(c);
	#elif defined(THOTH_ARCH_x86_64)
		thoth_vga_putc(c);
	#else
		// Do nothing
	#endif
}

void cstd_io_print(const char* str)
{
	#if defined(THOTH_ARCH_i686)
		thoth_vga_puts(str);
	#elif defined(THOTH_ARCH_x86_64)
		thoth_vga_puts(str);
	#else
		// Do nothing
	#endif
}
