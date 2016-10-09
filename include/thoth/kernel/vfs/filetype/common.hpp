/*
* 	filename	: common.hpp
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
#ifndef _THOTH_KERNEL_VFS_FILETYPE_COMMON_HPP
#define _THOTH_KERNEL_VFS_FILETYPE_COMMON_HPP 1

namespace Thoth
{
	namespace Kernel
	{
		namespace VFS
		{
			namespace FileType
			{
				enum class FileType
				{
					DATA = 0x1,
					DIR  = 0x2,
					SOCK = 0x3,
					LINK = 0x4,
				};
			}
		}
	}
}

// Header guard
#endif
