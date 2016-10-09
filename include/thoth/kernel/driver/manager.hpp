/*
* 	filename	: manager.hpp
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
#ifndef _THOTH_KERNEL_DRIVER_MANAGER_HPP
#define _THOTH_KERNEL_DRIVER_MANAGER_HPP 1

// Thoth headers
#include "thoth/std/util.hpp"
#include "thoth/kernel/driver/driver.hpp"
#include "thoth/std/container/stack.hpp"

#include "thoth/std/io.hpp"

namespace Thoth
{
	namespace Kernel
	{
		namespace Driver
		{
			struct Manager
			{
				Std::Container::Stack<Driver>* drivers;

				Status init()
				{
					this->drivers = new Std::Container::Stack<Driver>();

					return Status(STATUS_SUCCESS);
				}

				Status addHook(Driver driver)
				{
					this->drivers->append(driver);

					Std::IO::PrintFormat("[$F3DRIMGR$FF] Added hook to driver $F3%s$FF\n", driver.name);

					return Status(STATUS_SUCCESS);
				}

				Status initAll()
				{
					Std::IO::PrintLine("[$F3DRIMGR$FF] Starting driver load process...");

					for (size_t i = 0; i < this->drivers->getLength(); i ++)
					{
						Driver& driver =  (*this->drivers)[i];

						Std::IO::PrintFormat("[$F3DRIMGR$FF] Loading driver $F3%s$FF version $F3%i$FF.$F3%i$FF.$F3%i$FF : ", driver.name, driver.version.major, driver.version.minor, driver.version.build);

						Status status = driver.init_func();

						if (status.getSuccessful())
							Std::IO::Print("$F2SUCCESS$FF\n");
						else
						{
							Std::IO::PrintFormat("$F4FAILURE$FF [$F4Error %i$FF]\n", status.getError());
						}
					}

					return Status(STATUS_SUCCESS);
				}

				Status tickAll()
				{
					for (size_t i = 0; i < this->drivers->getLength(); i ++)
					{
						(*this->drivers)[i].tick_func();
					}

					return Status(STATUS_SUCCESS);
				}
			};
		}
	}
}

// Header guard
#endif
