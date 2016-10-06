/*
* 	filename	: vnode.hpp
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
				char name[MAX_NODE_NAME_SIZE];
				unsigned long id;

				VNode* parent;
				VNode* children[MAX_CHILD_NODES];

				VNode(const char* name)
				{
					for (int i = 0; i < MAX_NODE_NAME_SIZE && name[i] != '\0'; i ++)
					{
						this->name[i] = name[i];
					}

					for (int i = 0; i < MAX_CHILD_NODES; i ++)
						this->children[i] = nullptr;
				}

				Result<VNode*> addChild(const char* name)
				{
					for (int i = 0; i < MAX_CHILD_NODES; i ++)
					{
						if (this->children[i] == nullptr)
						{
							VNode* new_node = new VNode(name);
							new_node.parent = this;
						}
					}

					return Result<VNode*>(nullptr, 1);
				}


			}
		}
	}
}

#endif
