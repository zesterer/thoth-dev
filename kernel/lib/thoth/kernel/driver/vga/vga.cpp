/*
* 	filename	: vga.cpp
* 	component	: thoth
*
* 	This file is part of Thoth.
*
* 	Thoth is free software: you can redistribute it and/or modify
* 	it under the terms of the GNU General Public License as published by
* 	the Free Software Foundation, either version 3 of the License, or
* 	(at your option) any later version.
*
* 	Thoth is distributed in the hope that it will be useful,
* 	but WITHOUT ANY WARRANTY; without even the implied warranty of
* 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* 	GNU General Public License for more details.
*
* 	You should have received a copy of the GNU General Public License
* 	along with Thoth.  If not, see <http://www.gnu.org/licenses/>.
*/

// Thoth headers
#include "thoth/kernel/driver/vga/vga.hpp"
#include "thoth/kernel/driver/vga/screen.hpp"
#include "thoth/kernel/driver/portio/portio.hpp"

// GCC headers
#include "stdint.h"
#include "stddef.h"

namespace Thoth
{
	namespace Kernel
	{
		namespace Driver
		{
			namespace VGA
			{
				static uint8_t MakeColour(Colour fg, Colour bg);
				static uint16_t MakeEntry(char c, uint8_t colour);

				const size_t SCREEN_WIDTH = 80;
				const size_t SCREEN_HEIGHT = 25;

				size_t cursor_row;
				size_t cursor_column;
				uint8_t cursor_colour;
				uint16_t* screen_buffer;

				Status Init()
				{
					cursor_row = 0;
					cursor_column = 0;
					cursor_colour = MakeColour(Colour::WHITE, Colour::BLACK);
					screen_buffer = (uint16_t*)0xB8000;

					stdout.push = Push;

					for (size_t j = 0; j < SCREEN_HEIGHT; j ++)
					{
						for (size_t i = 0; i < SCREEN_WIDTH; i ++)
						{
							const size_t index = j * SCREEN_WIDTH + i;
							screen_buffer[index] = MakeEntry(' ', cursor_colour);
						}
					}

					return Status(STATUS_SUCCESS);
				}

				static uint8_t MakeColour(Colour fg, Colour bg)
				{
					return ((uint8_t)bg << 4) | (uint8_t)fg;
				}

				static uint16_t MakeEntry(char c, uint8_t colour)
				{
					return ((uint16_t)colour << 8) | (uint16_t)c;
				}

				void SetColour(Colour front_color, Colour back_color)
				{
					cursor_colour = MakeColour(front_color, back_color);
				}

				void PlaceEntry(char c, uint8_t colour, size_t i, size_t j)
				{
					const size_t index = j * SCREEN_WIDTH + i;
					screen_buffer[index] = MakeEntry(c, colour);
				}

				void PlaceCursor(int row, int column)
				{
					unsigned short pos = row * SCREEN_WIDTH + column;

				    // cursor LOW port to vga INDEX register
				    PortIO::Out8(0x3D4, 0x0F);
				    PortIO::Out8(0x3D5, (uint8_t)(pos & 0xFF));
				    // cursor HIGH port to vga INDEX register
				    PortIO::Out8(0x3D4, 0x0E);
				    PortIO::Out8(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
				}

				void PutChar(char c)
				{
					if (c == '\n')
					{
						cursor_column = 0;
						cursor_row ++;
					}
					else
					{
						PlaceEntry(c, cursor_colour, cursor_column, cursor_row);
						cursor_column ++;
					}

					if (cursor_column >= SCREEN_WIDTH)
					{
						cursor_column = 0;

						if (++cursor_row >= SCREEN_HEIGHT)
							cursor_row = 0;
					}

					PlaceCursor(cursor_row, cursor_column);
				}
			}
		}
	}
}
