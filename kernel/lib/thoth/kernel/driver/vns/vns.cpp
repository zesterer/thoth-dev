/*
* 	filename	: vns.cpp
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
#include "thoth/kernel/driver/vns/vns.hpp"
#include "thoth/kernel/vns/vns.hpp"
#include "thoth/std/io.hpp"

namespace Thoth
{
	namespace Kernel
	{
		namespace Driver
		{
			namespace VNS
			{
				/* Driver hook method definitions */

				Status Init();
				Status Tick();

				/* Driver generation method */

				Result<Driver> GenDriver()
				{
					return Result<Driver>(Driver("vns", SoftwareVersion(0, 1, 0), Init, Tick), STATUS_SUCCESS);
				}

				/* Driver code */

				/* Definitions */

				const unsigned short CMOS_PORT_IN = 0x70;
				const unsigned short CMOS_PORT_OUT = 0x71;

				Result<unsigned char> GetRegister(int i);

				unsigned char cmos_data[256];

				/* Code */

				Status Init()
				{
					Status status = Kernel::VNS::Init();

					if (status.getSuccessful())
					{
						unsigned long dir = (unsigned long)Kernel::VNS::NodeAttribute::DEFAULT_DIR;
						Kernel::VNS::Node* r0 = Thoth::Kernel::VNS::GetVNS().getValue()->getRoot().getValue();
						Kernel::VNS::Node* n1 = r0->addChild("bin", dir).getValue();
						Kernel::VNS::Node* n2 = n1->addChild("hello-world").getValue();
						Kernel::VNS::Node* n3 = r0->addChild("dev", dir).getValue();
						Kernel::VNS::Node* n4 = n3->addChild("serial", dir).getValue();
						Kernel::VNS::Node* n5 = n4->addChild("COM1").getValue();
						Kernel::VNS::Node* n6 = n4->addChild("COM2").getValue();
						Kernel::VNS::Node* n7 = n1->addChild("extra", dir).getValue();
						Kernel::VNS::Node* n8 = n7->addChild("test-exec").getValue();
						Kernel::VNS::Node* n9 = n7->addChild("examples", dir).getValue();
						r0->getNode("/bin/extra/./../extra/examples").getValue()->addChild("example0");
						r0->getNode("/bin/extra/./../extra/..").getValue()->addChild("testfile");

						/*
						Std::IO::Print("\n");
						Kernel::VNS::DisplayTree();
						*/
					}

					return status;
				}

				Status Tick()
				{
					return Kernel::VNS::Tick();
				}
			}
		}
	}
}
