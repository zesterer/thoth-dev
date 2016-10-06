/*
* 	filename	: file.hpp
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
#ifndef _THOTH_KERNEL_VFS_FILE_HPP
#define _THOTH_KERNEL_VFS_FILE_HPP 1

// Thoth headers
#include "thoth/std/util.hpp"

namespace Thoth
{
	namespace Kernel
	{
		namespace VFS
		{
			const int MAX_FILENAME_LENGTH = 256;

			union File;

			enum class FileType
			{
				NONE      = 0x0,
				BLOCK     = 0x1,
				DIRECTORY = 0x2,
				SOCKET    = 0x3,
				LINK      = 0x4,
			};

			struct BaseFile
			{
				char name[MAX_FILENAME_LENGTH];
				FileType type;
			};

			struct BlockFile : BaseFile
			{
				unsigned long data_reference;

				BlockFile();
			};

			struct DirectoryFile : BaseFile
			{
				File* children[64];

				DirectoryFile();
			};

			struct SocketFile : BaseFile
			{
				unsigned long socket_port;

				SocketFile();
			};

			struct LinkFile : BaseFile
			{
				File* target;

				LinkFile();
			};

			union File
			{
				BlockFile block_file;
				DirectoryFile directory_file;
				SocketFile socket_file;
				LinkFile link_file;
			};
		}
	}
}

// Header guard
#endif
