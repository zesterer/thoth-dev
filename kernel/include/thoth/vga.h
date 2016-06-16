#ifndef THOTH_KERNEL_THOTH_VGA
#define THOTH_KERNEL_THOTH_VGA

#include "cstd/com.h"

enum thoth_vga_color
{
	COLOR_BLACK		= 0,
	COLOR_BLUE		= 1,
	COLOR_GREEN		= 2,
	COLOR_CYAN		= 3,
	COLOR_RED		= 4,
	COLOR_MAGENTA		= 5,
	COLOR_BROWN		= 6,
	COLOR_LIGHT_GREY	= 7,
	COLOR_DARK_GREY		= 8,
	COLOR_LIGHT_BLUE	= 9,
	COLOR_LIGHT_GREEN	= 10,
	COLOR_LIGHT_CYAN	= 11,
	COLOR_LIGHT_RED		= 12,
	COLOR_LIGHT_MAGENTA	= 13,
	COLOR_LIGHT_BROWN	= 14,
	COLOR_WHITE		= 15,
};

extern const size_t THOTH_VGA_WIDTH;
extern const size_t THOTH_VGA_HEIGHT;

extern size_t thoth_vga_terminal_row;
extern size_t thoth_vga_terminal_column;
extern uint8_t thoth_vga_terminal_color;
extern uint16_t* thoth_vga_terminal_buffer;

uint8_t thoth_vga_make_color(enum thoth_vga_color fg, enum thoth_vga_color bg);
uint16_t thoth_vga_make_entry(char c, uint8_t color);

void thoth_vga_set_color(uint8_t front_color, uint8_t back_color);
void thoth_vga_put_entry(char c, uint8_t color, size_t i, size_t j);

int thoth_vga_init();
void thoth_vga_putc(char c);
void thoth_vga_puts(const char* str);

#endif
