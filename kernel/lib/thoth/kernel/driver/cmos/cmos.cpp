/*
* 	filename	: cmos.cpp
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
#include "thoth/kernel/driver/cmos/cmos.hpp"
#include "thoth/kernel/driver/portio/portio.hpp"

namespace Thoth
{
	namespace Kernel
	{
		namespace Driver
		{
			namespace CMOS
			{
				const unsigned short CMOS_PORT_IN = 0x70;
				const unsigned short CMOS_PORT_OUT = 0x70;

				unsigned char cmos_data[128];

				Status Init()
				{
					return Status(STATUS_SUCCESS);
				}

				Status Update()
				{
					for (int i = 0; i < 128; i ++)
					{
						PortIO::Out8(CMOS_PORT_IN, (unsigned char)i);
						cmos_data[i] = PortIO::In8(CMOS_PORT_OUT).getValue();
					}

					return Status(STATUS_SUCCESS);
				}

				Result<unsigned char> GetRegister(int i)
				{
					return Result<unsigned char>(cmos_data[i], STATUS_SUCCESS);
				}
			}
		}
	}
}
