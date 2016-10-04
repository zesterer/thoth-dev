/*
* 	filename	: serial.cpp
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
#include "thoth/kernel/driver/serial/serial.hpp"
#include "thoth/kernel/driver/portio/portio.hpp"

// GCC headers
#include "stdint.h"

namespace Thoth
{
	namespace Kernel
	{
		namespace Driver
		{
			namespace Serial
			{
				Status Init()
				{
					return Status(STATUS_SUCCESS);
				}

				Status InitPort(Port port, int baudrate, char databits, char stopbits, Parity parity)
				{
					PortIO::Out8((unsigned short)port + 1, 0x00); // Disable all interrupts
					PortIO::Out8((unsigned short)port + 3, 0x80); // Enable DLAB (set baud rate divisor)
					PortIO::Out8((unsigned short)port + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
					PortIO::Out8((unsigned short)port + 1, 0x00); // Set divisor to 3 (hi byte) 38500 baud
					PortIO::Out8((unsigned short)port + 3, 0x03); // 8 bits, no parity, one stop bit
					PortIO::Out8((unsigned short)port + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
					PortIO::Out8((unsigned short)port + 4, 0x0B); // IRQs enabled, RTS/DSR set

					return Status(STATUS_SUCCESS);
				}

				bool DataReceived(Port port)
				{
					return (PortIO::In8((unsigned short)port + 5).getValue() & 0x1) != 0;
				}

				Result<char> ReadData(Port port)
				{
					while (!DataReceived(port));

					return Result<char>(PortIO::In8((unsigned short)port).getValue(), STATUS_SUCCESS);
				}

				bool CanWrite(Port port)
				{
					return (PortIO::In8((unsigned short)port + 5).getValue() & 0x20) != 0;
				}

				Status Write(Port port, char c)
				{
					while (!CanWrite(port));

					PortIO::Out8((unsigned short)port, c);

					return Status(STATUS_SUCCESS);
				}

				Status WriteData(Port port, const unsigned char* s, size_t n)
				{
					for (size_t i = 0; i < n; i ++)
						Write(port, s[i]);

					return Status(STATUS_SUCCESS);
				}

				Status WriteStr(Port port, const char* s)
				{
					for (size_t i = 0; s[i] != '\0'; i ++)
						Write(port, s[i]);

					return Status(STATUS_SUCCESS);
				}
			}
		}
	}
}
