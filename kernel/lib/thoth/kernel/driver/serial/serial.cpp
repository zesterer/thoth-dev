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
				const int UART_CLOCK_TICK_RATE = 115200;

				Status Init()
				{
					return Status(STATUS_SUCCESS);
				}

				Status InitPort(Port port, int baudrate, unsigned char databits, unsigned char stopbits, Parity parity)
				{
					// Calculate a divisor value for the baudrate
					unsigned short divisor = (unsigned short)(UART_CLOCK_TICK_RATE / baudrate);

					PortIO::Out8((unsigned short)port + 1, 0x00); // Disable all interrupts
					PortIO::Out8((unsigned short)port + 3, 0x80); // Enable DLAB (set baud rate divisor)

					// Divisor short value
					PortIO::Out8((unsigned short)port + 0, ((divisor >> 0) & 0xFF)); // Set divisor (lo byte)
					PortIO::Out8((unsigned short)port + 1, ((divisor >> 8) & 0xFF)); // Set divisor (hi byte)

					/* Serial configuration parameters */

					unsigned char databits_val = 0;
					unsigned char stopbits_val = 0;

					// Find databits value equivalent
					switch (databits)
					{
						case (5):
							databits_val = 0x0;
							break;
						case (6):
							databits_val = 0x1;
							break;
						case (7):
							databits_val = 0x2;
							break;
						case (8):
						default:
							databits_val = 0x3;
							break;
					}

					// Find stopbits value equivalent
					switch (stopbits)
					{
						case (1):
							stopbits_val = 0x4;
							break;
						case (2):
						default:
							stopbits_val = 0x0;
							break;
					}

					unsigned char serial_config = databits_val | stopbits_val | (unsigned char)parity;
					PortIO::Out8((unsigned short)port + 3, serial_config); // 8 bits, no parity, one stop bit
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
