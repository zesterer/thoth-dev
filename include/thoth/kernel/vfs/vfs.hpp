/*
* 	filename	: vfs.hpp
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
#ifndef _THOTH_KERNEL_VFS_VFS_HPP
#define _THOTH_KERNEL_VFS_VFS_HPP 1

// Thoth headers
#include "thoth/std/util.hpp"
#include "thoth/kernel/vfs/file.hpp"

namespace Thoth
{
	namespace Kernel
	{
		namespace VFS
		{
			struct VFS
			{
				File root_file;
			};
		}
	}
}

// Header guard
#endif
