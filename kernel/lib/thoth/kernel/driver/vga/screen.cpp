/*
* 	filename	: screen.cpp
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
#include "thoth/kernel/driver/vga/screen.hpp"
#include "thoth/kernel/driver/vga/vga.hpp"

#include "thoth/port.h"

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
				static bool char_is_hex(char c)
				{
					if (c >= '0' && c <= '9') return true;
					if (c >= 'a' && c <= 'z') return true;
					if (c >= 'A' && c <= 'Z') return true;
					return false;
				}

				static uint8_t char_to_hex(char c)
				{
					if (c >= '0' && c <= '9') return c - '0';
					if (c >= 'a' && c <= 'f') return 10 + c - 'a';
					if (c >= 'A' && c <= 'F') return 10 + c - 'A';
					return 0;
				}

				Result<size_t> Push(const unsigned char* data, size_t n)
				{
					for (size_t i = 0; i < n; i ++)
					{
						int16_t escaped = 0;

						if (data[i] == '$' && i + 1 < n)
						{
							if (escaped == 0 && data[i + 1] == 'F' && i + 2 < n)
							{
								if (char_is_hex(data[i + 2]))
								{
									escaped = 1;

									#if defined(THOTH_ARCH_x86_64) || defined(THOTH_ARCH_i686)
										Thoth::Kernel::Driver::VGA::SetColour((Thoth::Kernel::Driver::VGA::Colour)char_to_hex(data[i + 2]), (Thoth::Kernel::Driver::VGA::Colour)(Thoth::Kernel::Driver::VGA::cursor_colour >> 4));
									#else
										// Do nothing
									#endif

									i += 2;
								}
							}

							if (escaped == 0 && data[i + 1] == 'B' && i + 2 < n)
							{
								if (char_is_hex(data[i + 2]))
								{
									escaped = 1;

									#if defined(THOTH_ARCH_x86_64) || defined(THOTH_ARCH_i686)
										Thoth::Kernel::Driver::VGA::SetColour((Thoth::Kernel::Driver::VGA::Colour)(Thoth::Kernel::Driver::VGA::cursor_colour & 0xF), (Thoth::Kernel::Driver::VGA::Colour)char_to_hex(data[i + 2]));
									#else
										// Do nothing
									#endif

									i += 2;
								}
							}
						}

						if (escaped != 1)
						{
							#if defined(THOTH_ARCH_x86_64) || defined(THOTH_ARCH_i686)
								Thoth::Kernel::Driver::VGA::PutChar(data[i]);
							#else
								// Do nothing
							#endif
						}
					}

					return 0;
				}

				Std::Stream::Stream stdout;
			}
		}
	}
}
