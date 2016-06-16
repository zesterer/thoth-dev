#include "cstd/io.h"
#include "cstd/str.h"
#include "thoth/vga.h"

uint8_t thoth_vga_make_color(enum thoth_vga_color fg, enum thoth_vga_color bg)
{
	return (bg << 4) | fg;
}

uint16_t thoth_vga_make_entry(char c, uint8_t color)
{
	return ((uint16_t)color << 8) | (uint16_t)c;
}

const size_t THOTH_VGA_WIDTH = 80;
const size_t THOTH_VGA_HEIGHT = 25;

size_t thoth_vga_terminal_row;
size_t thoth_vga_terminal_column;
uint8_t thoth_vga_terminal_color;
uint16_t* thoth_vga_terminal_buffer;

int thoth_vga_init()
{
	thoth_vga_terminal_row = 0;
	thoth_vga_terminal_column = 0;
	thoth_vga_terminal_color = thoth_vga_make_color(COLOR_WHITE, COLOR_BLACK);
	thoth_vga_terminal_buffer = (uint16_t*)0xB8000;

	for (size_t j = 0; j < THOTH_VGA_HEIGHT; j ++)
	{
		for (size_t i = 0; i < THOTH_VGA_WIDTH; i ++)
		{
			const size_t index = j * THOTH_VGA_WIDTH + i;
			thoth_vga_terminal_buffer[index] = thoth_vga_make_entry(' ', thoth_vga_terminal_color);
		}
	}

	return 0;
}

void thoth_vga_set_color(uint8_t front_color, uint8_t back_color)
{
	thoth_vga_terminal_color = thoth_vga_make_color(front_color, back_color);
}

void thoth_vga_put_entry(char c, uint8_t color, size_t i, size_t j)
{
	const size_t index = j * THOTH_VGA_WIDTH + i;
	thoth_vga_terminal_buffer[index] = thoth_vga_make_entry(c, color);
}

void thoth_vga_putc(char c)
{
	if (c == '\n')
	{
		thoth_vga_terminal_column = 0;
		thoth_vga_terminal_row ++;
	}
	else
	{
		thoth_vga_put_entry(c, thoth_vga_terminal_color, thoth_vga_terminal_column, thoth_vga_terminal_row);
		thoth_vga_terminal_column ++;
	}

	if (thoth_vga_terminal_column >= THOTH_VGA_WIDTH)
	{
		thoth_vga_terminal_column = 0;

		if (++thoth_vga_terminal_row >= THOTH_VGA_HEIGHT)
			thoth_vga_terminal_row = 0;
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

void thoth_vga_puts(const char* str)
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
					thoth_vga_set_color(char_to_hex(str[i + 2]), thoth_vga_terminal_color >> 4);
					i += 2;
				}
			}

			if (escaped == 0 && str[i + 1] == 'B' && i + 2 < len)
			{
				if (char_is_hex(str[i + 2]))
				{
					escaped = 1;
					thoth_vga_set_color(thoth_vga_terminal_color & 0xF, char_to_hex(str[i + 2]));
					i += 2;
				}
			}
		}

		if (escaped != 1)
		{
			thoth_vga_putc(str[i]);
		}
	}
}
