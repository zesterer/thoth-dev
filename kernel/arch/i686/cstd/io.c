#include "cstd/io.h"
#include "cstd/str.h"

enum vga_color
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

uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
	return (bg << 4) | fg;
}

uint16_t make_vga_entry(char c, uint8_t color)
{
	return ((uint16_t)color << 8) | (uint16_t)c;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_set_color(uint8_t front_color, uint8_t back_color)
{
	terminal_color = make_color(front_color, back_color);
}

void terminal_put_entry_at(char c, uint8_t color, size_t i, size_t j)
{
	const size_t index = j * VGA_WIDTH + i;
	terminal_buffer[index] = make_vga_entry(c, color);
}

void cstd_io_put(char c)
{
	if (c == '\n')
	{
		terminal_column = 0;
		terminal_row ++;
	}
	else
	{
		terminal_put_entry_at(c, terminal_color, terminal_column, terminal_row);
		terminal_column ++;
	}

	if (terminal_column >= VGA_WIDTH)
	{
		terminal_column = 0;

		if (++terminal_row >= VGA_HEIGHT)
			terminal_row = 0;
	}
}

bool char_is_hex(char c)
{
	if (c >= '0' && c <= '9') return true;
	if (c >= 'a' && c <= 'z') return true;
	if (c >= 'A' && c <= 'Z') return true;
	return false;
}

uint8_t char_to_hex(char c)
{
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'a' && c <= 'f') return 10 + c - 'a';
	if (c >= 'A' && c <= 'F') return 10 + c - 'A';
	return 0;
}

void cstd_io_init()
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_WHITE, COLOR_BLACK);
	terminal_buffer = (uint16_t*)0xB8000;

	for (size_t j = 0; j < VGA_HEIGHT; j ++)
	{
		for (size_t i = 0; i < VGA_WIDTH; i ++)
		{
			const size_t index = j * VGA_WIDTH + i;
			terminal_buffer[index] = make_vga_entry(' ', terminal_color);
		}
	}
}

void cstd_io_print(const char* str)
{
	size_t len = cstd_str_length(str);

	for (size_t i = 0; i < len; i ++)
	{
		int16_t escaped = 0;

		if (str[i] == '$' && i + 1 < len)
		{
			if (escaped == 0 && str[i + 1] == 'F' && i + 2 < len)
			{
				if (char_is_hex(str[i + 2]))
				{
					escaped = 1;
					terminal_set_color(char_to_hex(str[i + 2]), terminal_color >> 4);
					i += 2;
				}
			}

			if (escaped == 0 && str[i + 1] == 'B' && i + 2 < len)
			{
				if (char_is_hex(str[i + 2]))
				{
					escaped = 1;
					terminal_set_color(terminal_color & 0xF, char_to_hex(str[i + 2]));
					i += 2;
				}
			}
		}

		if (escaped != 1)
		{
			cstd_io_put(str[i]);
		}
	}
}
