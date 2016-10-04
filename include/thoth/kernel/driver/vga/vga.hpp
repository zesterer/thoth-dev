/*
* 	filename	: vga.hpp
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

// Header guard
#ifndef _THOTH_KERNEL_DRIVER_VGA_VGA_HPP
#define _THOTH_KERNEL_DRIVER_VGA_VGA_HPP 1

// Thoth headers
#include "thoth/std/util.hpp"

namespace Thoth
{
	namespace Kernel
	{
		namespace Driver
		{
			namespace VGA
			{
				enum class Colour
				{
					BLACK         = 0x0,
					BLUE          = 0x1,
					GREEN         = 0x2,
					CYAN          = 0x3,
					RED           = 0x4,
					MAGENTA       = 0x5,
					BROWN         = 0x6,
					LIGHT_GREY    = 0x7,
					DARK_GREY     = 0x8,
					LIGHT_BLUE    = 0x9,
					LIGHT_GREEN   = 0xA,
					LIGHT_CYAN    = 0xB,
					LIGHT_RED     = 0xC,
					LIGHT_MAGENTA = 0xD,
					LIGHT_BROWN   = 0XE,
					WHITE         = 0xF,
				};

				extern unsigned char cursor_colour;

				Result<char> Init();

				void SetColour(Colour front_color, Colour back_color);
				void PlaceCursor(int row, int column);
				void PutChar(char c);
			}
		}
	}
}

// Header guard
#endif
