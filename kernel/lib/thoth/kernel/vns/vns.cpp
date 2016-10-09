/*
* 	filename	: vns.cpp
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
#include "thoth/kernel/vns/vns.hpp"
#include "thoth/std/io.hpp"

namespace Thoth
{
	namespace Kernel
	{
		namespace VNS
		{
			VNS* glob_vns = nullptr;

			VNS::VNS()
			{
				this->root = new Node((char*)"root", (unsigned long)NodeAttribute::DEFAULT_DIR);
			}

			Result<Node*> VNS::getRoot()
			{
				return Result<Node*>(this->root, this->root != nullptr ? STATUS_SUCCESS : STATUS_FAILURE);
			}

			Status Init()
			{
				glob_vns = new VNS();

				return Status(STATUS_SUCCESS);
			}

			Result<VNS*> GetVNS()
			{
				if (glob_vns == nullptr)
					return Result<VNS*>(nullptr, STATUS_FAILURE);
				else
					return Result<VNS*>(glob_vns, STATUS_SUCCESS);
			}

			static void DisplayNode(Node* node, int depth)
			{
				for (int i = 0; i < depth; i ++)
					Std::IO::Print("|  ");

				if (depth > 8)
				{
					Std::IO::Print("$F4Max depth reached!$FF\n");
					return;
				}

				if ((node->flags & (unsigned long)NodeAttribute::PARENT) == 0)
				{
					Std::IO::Print("$F2FILE$FF ");
					Std::IO::Print(node->name);
					Std::IO::Print("\n");
				}
				else if (node->flags & (unsigned long)NodeAttribute::PARENT)
				{
					Std::IO::Print("$F3DIR$FF ");
					Std::IO::Print(node->name);
					Std::IO::Print("\n");

					for (size_t i = 0; i < NODE_MAX_CHILDREN; i ++)
					{
						if (node->children[i] != NULL)
							DisplayNode(node->children[i], depth + 1);
					}
				}
			}

			Status DisplayMap()
			{
				Std::IO::PrintLine("Displaying Virtual Node System...");
				DisplayNode(GetVNS().getValue()->root, 0);

				return Status(STATUS_SUCCESS);
			}
		}
	}
}
