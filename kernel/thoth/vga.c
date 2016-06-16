#include "cstd/io.h"
#include "cstd/str.h"
#include "thoth/vga.h"
#include "thoth/port.h"

const size_t THOTH_VGA_WIDTH = 80;
const size_t THOTH_VGA_HEIGHT = 25;

size_t thoth_vga_terminal_row;
size_t thoth_vga_terminal_column;
uint8_t thoth_vga_terminal_color;
uint16_t* thoth_vga_terminal_buffer;

static uint8_t thoth_vga_make_color(enum thoth_vga_color fg, enum thoth_vga_color bg);
static uint16_t thoth_vga_make_entry(char c, uint8_t color);

static uint8_t thoth_vga_make_color(enum thoth_vga_color fg, enum thoth_vga_color bg)
{
	return (bg << 4) | fg;
}

static uint16_t thoth_vga_make_entry(char c, uint8_t color)
{
	return ((uint16_t)color << 8) | (uint16_t)c;
}

int thoth_vga_init()
{
	thoth_vga_terminal_row = 0;
	thoth_vga_terminal_column = 0;
	thoth_vga_terminal_color = thoth_vga_make_color(THOTH_VGA_WHITE, THOTH_VGA_BLACK);
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

void thoth_vga_update_cursor(int row, int column)
{
	unsigned short pos = row * THOTH_VGA_WIDTH + column;

    // cursor LOW port to vga INDEX register
    thoth_port_outb(0x3D4, 0x0F);
    thoth_port_outb(0x3D5, (unsigned char)(pos & 0xFF));
    // cursor HIGH port to vga INDEX register
    thoth_port_outb(0x3D4, 0x0E);
    thoth_port_outb(0x3D5, (unsigned char )((pos >> 8) & 0xFF));
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

	thoth_vga_update_cursor(thoth_vga_terminal_row, thoth_vga_terminal_column);
}
