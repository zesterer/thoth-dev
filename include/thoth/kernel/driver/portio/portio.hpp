/*
* 	filename	: portio.hpp
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
#ifndef _THOTH_KERNEL_DRIVER_PORTIO_PORTIO_HPP
#define _THOTH_KERNEL_DRIVER_PORTIO_PORTIO_HPP 1

// Thoth headers
#include "thoth/std/util.hpp"

namespace Thoth
{
	namespace Kernel
	{
		namespace Driver
		{
			namespace PortIO
			{
				Status Out8(unsigned short port, unsigned char value);
				Status Out16(unsigned short port, unsigned short value);
				Status Out32(unsigned short port, unsigned int value);

				Result<unsigned char> In8(unsigned short port);
				Result<unsigned short> In16(unsigned short port);
				Result<unsigned int> In32(unsigned short port);
			}
		}
	}
}

// Header guard
#endif
