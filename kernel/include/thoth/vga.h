#ifndef THOTH_KERNEL_THOTH_VGA
#define THOTH_KERNEL_THOTH_VGA

#include "cstd/com.h"

enum thoth_vga_color
{
	THOTH_VGA_BLACK			= 0,
	THOTH_VGA_BLUE			= 1,
	THOTH_VGA_GREEN			= 2,
	THOTH_VGA_CYAN			= 3,
	THOTH_VGA_RED			= 4,
	THOTH_VGA_MAGENTA		= 5,
	THOTH_VGA_BROWN			= 6,
	THOTH_VGA_LIGHT_GREY	= 7,
	THOTH_VGA_DARK_GREY		= 8,
	THOTH_VGA_LIGHT_BLUE	= 9,
	THOTH_VGA_LIGHT_GREEN	= 10,
	THOTH_VGA_LIGHT_CYAN	= 11,
	THOTH_VGA_LIGHT_RED		= 12,
	THOTH_VGA_LIGHT_MAGENTA	= 13,
	THOTH_VGA_LIGHT_BROWN	= 14,
	THOTH_VGA_WHITE			= 15,
};

int thoth_vga_init();
void thoth_vga_putc(char c);
void thoth_vga_puts(const char* str);

#endif
