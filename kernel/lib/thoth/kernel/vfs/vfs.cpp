/*
* 	filename	: vfs.cpp
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
#include "thoth/kernel/vfs/vfs.hpp"

namespace Thoth
{
	namespace Kernel
	{
		namespace VFS
		{
			VFS global_vfs;

			Status VFS::init()
			{
				Status status = this->root.dir_file.init();

				if (status.getSuccessful())
					this->initiated = true;

				return status;
			}

			Status Init()
			{
				return global_vfs.init();
			}

			Result<File*> GetRoot()
			{
				if (global_vfs.isInitiated())
					return Result<File*>(&global_vfs.root, STATUS_SUCCESS);
				else
					return Result<File*>(nullptr, 1);
			}
		}
	}
}
