/*
* 	filename	: portio.cpp
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
#include "thoth/std/util.hpp"
#include "thoth/kernel/driver/portio/portio.hpp"

// GCC headers
#include "stdint.h"

namespace Thoth
{
	namespace Kernel
	{
		namespace Driver
		{
			namespace PortIO
			{
				Status Out8(unsigned short port, unsigned char value)
				{
					asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
					return Status(STATUS_SUCCESS);
				}

				Status Out16(unsigned short port, unsigned short value)
				{
					asm volatile ("outw %0, %1" : : "a"(value), "Nd"(port));
					return Status(STATUS_SUCCESS);
				}

				Status Out32(unsigned short port, unsigned int value)
				{
					asm volatile ("outl %0, %1" : : "a"(value), "Nd"(port));
					return Status(STATUS_SUCCESS);
				}

				Result<unsigned char> In8(unsigned short port)
				{
					uint8_t ret;
					asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
					return Result<unsigned char>(ret, STATUS_SUCCESS);
				}

				Result<unsigned short> In16(unsigned short port)
				{
					uint16_t ret;
					asm volatile ("inw %1, %0" : "=a"(ret) : "Nd"(port));
					return Result<unsigned short>(ret, STATUS_SUCCESS);
				}

				Result<unsigned int> In32(unsigned short port)
				{
					uint32_t ret;
					asm volatile ("inl %1, %0" : "=a"(ret) : "Nd"(port));
					return Result<unsigned int>(ret, STATUS_SUCCESS);
				}
			}
		}
	}
}
