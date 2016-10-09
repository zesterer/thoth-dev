/*
* 	filename	: node.hpp
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
#ifndef _THOTH_KERNEL_VNS_NODE_HPP
#define _THOTH_KERNEL_VNS_NODE_HPP 1

// Thoth headers
#include "thoth/kernel/vns/glob.hpp"

namespace Thoth
{
	namespace Kernel
	{
		namespace VNS
		{
			struct Node
			{
				unsigned long flags = (unsigned long)NodeAttribute::DEFAULT_FILE;

				char* name = nullptr;
				Node* parent = nullptr;

				Node* children[32];

				Node(char* name, unsigned long flags = (unsigned long)NodeAttribute::DEFAULT_FILE);
				Result<Node*> addChild(char* name, unsigned long flags = (unsigned long)NodeAttribute::DEFAULT_FILE);
				Result<Node*> getParent();
				Result<Node*> getRoot();
				Result<Node*> getChild(const char* name);
				Result<Node*> getNode(const char* nodename);
			};
		}
	}
}

// Header guard
#endif
