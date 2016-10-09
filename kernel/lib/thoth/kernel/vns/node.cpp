/*
* 	filename	: node.cpp
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
#include "thoth/kernel/vns/node.hpp"

namespace Thoth
{
	namespace Kernel
	{
		namespace VNS
		{
			Node::Node(char* name, unsigned long flags)
			{
				this->name = name;
				this->flags = flags;
			}

			Result<Node*> Node::addChild(char* name, unsigned long flags)
			{
				if ((this->flags & (unsigned long)NodeAttribute::PARENT) == 0)
					return Result<Node*>(nullptr, STATUS_FAILURE);

				for (size_t i = 0; i < NODE_MAX_CHILDREN; i ++)
				{
					if (this->children[i] == nullptr)
					{
						this->children[i] = new Node(name, flags);
						this->children[i]->parent = this;
						return Result<Node*>(this->children[i], STATUS_SUCCESS);
					}
				}

				return Result<Node*>(nullptr, STATUS_FAILURE);
			}

			Result<Node*> Node::getChild(const char* name)
			{
				for (size_t i = 0; i < NODE_MAX_CHILDREN; i ++)
				{
					if (this->children[i] == nullptr)
						continue;

					bool match = true;
					for (size_t j = 0; ; j ++)
					{
						if (this->children[i]->name[j] == '\0')
							break;
						if (name[j] == '\0')
							break;
						if (name[j] == NODENAME_DELIMITER)
							break;

						if (name[j] != this->children[i]->name[j])
						{
							match = false;
							break;
						}
					}

					if (match)
						return Result<Node*>(this->children[i], STATUS_SUCCESS);
				}

				return Result<Node*>(nullptr, STATUS_FAILURE);
			}

			Result<Node*> Node::getNode(const char* nodename)
			{
				size_t i = 0;
				size_t name_start = 0;

				for (; nodename[i] == '/'; i ++) {}

				name_start = i;

				for (; ; i ++)
				{
					if (nodename[i] == NODENAME_DELIMITER || nodename[i] == '\0')
					{
						Node* child = this->getChild(nodename + name_start).getValue();

						if (child == nullptr)
							return Result<Node*>(nullptr, STATUS_FAILURE);

						if (nodename[i] == NODENAME_DELIMITER)
							return child->getNode(nodename + i + 1);
						else if (nodename[i] == '\0')
							return Result<Node*>(child, STATUS_SUCCESS);
						else
							Result<Node*>(nullptr, STATUS_FAILURE);
					}
				}

				return Result<Node*>(nullptr, STATUS_FAILURE);
			}
		}
	}
}
