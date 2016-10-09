/*
* 	filename	: stack.hpp
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
#ifndef _THOTH_STD_CONTAINER_STACK_HPP
#define _THOTH_STD_CONTAINER_STACK_HPP 1

// Thoth headers
#include "thoth/std/util.hpp"

#include "libc/stdlib.h"

namespace Thoth
{
	namespace Std
	{
		namespace Container
		{
			template<typename T>
			struct Stack
			{
			private:

					T* array;
					size_t len;
					size_t size;

			public:

				Stack()
				{
					this->array = (T*)malloc(sizeof(T) * 1);
					this->len = 0;
					this->size = 1;
				};

				Status append(T item)
				{
					this->preUpdate();

					this->array[this->len] = item;
					this->len ++;

					this->postUpdate();

					return Status(STATUS_SUCCESS);
				}

				T& operator[](size_t i)
				{
					return this->array[i];
				}

				size_t getLength()
				{
					return this->len;
				}

			private:

				void preUpdate()
				{
					if (this->len >= this->size)
					{
						this->size *= 2;
						this->array = (T*)realloc(this->array, sizeof(T) * this->size);
					}
				}

				void postUpdate()
				{
					if (this->size >= 2 && this->size >= this->len * 3)
					{
						this->size /= 2;
						this->array = (T*)realloc(this->array, sizeof(T) * this->size);
					}
				}
			};
		}
	}
}

// Header guard
#endif
