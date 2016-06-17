#ifndef THOTH_KERNEL_THOTH_VGA
#define THOTH_KERNEL_THOTH_VGA

#include "stddef.h"
#include "stdint.h"

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

extern const size_t THOTH_VGA_WIDTH;
extern const size_t THOTH_VGA_HEIGHT;

extern size_t thoth_vga_terminal_row;
extern size_t thoth_vga_terminal_column;
extern uint8_t thoth_vga_terminal_color;
extern uint16_t* thoth_vga_terminal_buffer;

void thoth_vga_set_color(uint8_t front_color, uint8_t back_color);
void thoth_vga_put_entry(char c, uint8_t color, size_t i, size_t j);

int thoth_vga_init();
void thoth_vga_putc(char c);
void thoth_vga_puts(const char* str);

#endif
