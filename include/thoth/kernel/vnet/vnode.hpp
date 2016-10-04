/*
* 	filename	: vnode.hpp
* 	component	: thoth
* 	description	: Virtual Network Node definitions
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

#ifndef _THOTH_KERNEL_VNET_VNODE_H
#define _THOTH_KERNEL_VNET_VNODE_H 1

namespace Thoth
{
	namespace Kernel
	{
		namespace VNet
		{
			struct VNode
			{
				char name[256];
				unsigned long id;

				VNode* parent;
				VNode* children[64];
			}
		}
	}
}

#endif // #ifndef _THOTH_KERNEL_VNET_VNODE_H
