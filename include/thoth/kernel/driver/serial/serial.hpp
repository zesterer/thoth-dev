/*
* 	filename	: serial.hpp
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
#ifndef _THOTH_KERNEL_DRIVER_SERIAL_SERIAL_HPP
#define _THOTH_KERNEL_DRIVER_SERIAL_SERIAL_HPP 1

// Thoth headers
#include "thoth/std/util.hpp"
#include "thoth/kernel/driver/driver.hpp"

// GCC Headers
#include "stddef.h"

namespace Thoth
{
	namespace Kernel
	{
		namespace Driver
		{
			namespace Serial
			{
				enum class Port
				{
					COM1 = 0x3F8,
					COM2 = 0x2F8,
					COM3 = 0x3E8,
					COM4 = 0x2E8,
				};

				enum class Parity
				{
					NONE =  (0x0 << 3),
					ODD =   (0x1 << 3),
					EVEN =  (0x3 << 3),
					MARK =  (0x5 << 3),
					SPACE = (0x7 << 3),
				};

				Status Init();

				Status InitPort(Port port, int baudrate, unsigned char databits, unsigned char stopbits, Parity parity);

				bool DataReceived(Port port);
				Result<char> ReadData(Port port);

				bool CanWrite(Port port);
				Status Write(Port port, char c);
				Status WriteData(Port port, const unsigned char* s, size_t n);
				Status WriteStr(Port port, const char* s);

				Result<Driver*> GenerateDriver();
			}
		}
	}
}

// Header guard
#endif
