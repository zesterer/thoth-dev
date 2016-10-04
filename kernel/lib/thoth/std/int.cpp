/*
* 	filename	: int.cpp
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
#include "thoth/std/util.hpp"
#include "thoth/std/int.hpp"

// GCC headers
#include "stddef.h"
#include "stdint.h"

namespace Thoth
{
	namespace Std
	{
		namespace IO { extern Result<const char*> PrintLine(const char* s); }

		namespace Int
		{
			int Abs(int n)
			{
				return n < 0 ? -n : n;
			}

			int FromStr(const char* str)
			{
				int sign = 1;
				int total = 0;

				for (size_t i = 0; str[i] != '\0'; i ++)
				{
					total *= 10;

					if (str[i] == '-')
						sign *= -1;
					else if (str[i] == '+')
						sign *= 1;
					else if (str[i] >= 48 && str[i] <= 58)
						total += str[i] - 48;
					else
						return 0;
				}

				return total * sign;
			}

			char* ToStr(int value, char* str, int base)
			{
				long v = 1;
				int i = 0;

				if (base < 2 || base > 32)
					return str;

				if (value < 0)
				{
					str[i] = '-';
					i ++;
				}

				value = Abs(value);

				while (v < UINT32_MAX / base)
					v *= base;

				while (v > 0)
				{
					if (value / v > 0)
					{
						if (((value % (v * base)) / v) % base > 10)
							str[i] = 'A' + (value / v) % base - 10;
						else
							str[i] = '0' + (value / v) % base;

						i ++;
					}
					v /= base;
				}

				if (value == 0)
				{
					str[i] = '0';
					i ++;
				}

				str[i] = '\0';
				return str;
			}
		}
	}
}
