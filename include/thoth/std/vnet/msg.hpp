/*
* 	filename	: msg.hpp
* 	component	: thoth
* 	description	: Virtual Network Message definitions
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

#ifndef _THOTH_STD_VNET_MSG_H
#define _THOTH_STD_VNET_MSG_H 1

namespace Thoth
{
	namespace Std
	{
		namespace VNet
		{
			struct Msg
			{
			private:
				char* src_path;
				char* dest_path;

			public:
				char* getSource();
				char* getDestination();
			}
		}
	}
}

#endif // #ifndef _THOTH_STD_VNET_MSG_H
