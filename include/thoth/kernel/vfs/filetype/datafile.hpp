/*
* 	filename	: blockfile.hpp
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
#ifndef _THOTH_KERNEL_VFS_FILETYPE_DATAFILE_HPP
#define _THOTH_KERNEL_VFS_FILETYPE_DATAFILE_HPP 1

// Thoth headers
#include "thoth/kernel/vfs/filetype/basefile.hpp"

namespace Thoth
{
	namespace Kernel
	{
		namespace VFS
		{
			namespace FileType
			{
				struct DataFile : BaseFile
				{
					size_t data_ref;

					Status init()
					{
						this->type = FileType::DATA;

						this->data_ref = 0;

						return STATUS_SUCCESS;
					}
				};
			}
		}
	}
}

// Header guard
#endif
