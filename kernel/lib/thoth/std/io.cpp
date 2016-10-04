/*
* 	filename	: io.cpp
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
#include "thoth/std/io.hpp"
#include "thoth/kernel/driver/vga/screen.hpp"
#include "thoth/std/char.hpp"
#include "thoth/std/int.hpp"

#include "libc/string.h"

namespace Thoth
{
	namespace Std
	{
		namespace IO
		{
			Result<const char*> Print(const char* s)
			{
				Kernel::Driver::VGA::stdout.push((unsigned char*)s, strlen(s));

				return Result<const char*>(s, STATUS_SUCCESS);
			}

			Result<const char*> PrintLine(const char* s)
			{
				Kernel::Driver::VGA::stdout.push((unsigned char*)s, strlen(s));
				Kernel::Driver::VGA::stdout.push((unsigned char*)"\n", 2);

				return Result<const char*>(s, STATUS_SUCCESS);
			}

			Result<const char*> PrintFormat(const char* format, ...)
			{
				size_t len = 0;
				size_t format_len = strlen(format);

				__builtin_va_list args;
				__builtin_va_start(args, format);

				size_t last = 0;
				size_t i;
				for (i = 0; i < format_len; i ++)
				{
					switch (format[i])
					{
						case '%':
						{
							if (i >= format_len - 1) // Make sure we're not at the end of the string
								break;

							switch (format[i + 1])
							{
								case 's': // We're writing a string
								{
									Kernel::Driver::VGA::stdout.push((unsigned char*)&(format[last]), i - last); // Write the string so far
									// Write the string we found in the gap
									char* str = __builtin_va_arg(args, char*);
									Kernel::Driver::VGA::stdout.push((unsigned char*)str, strlen(str)); // Write the inserted string
									len += strlen(str);
									last = i + 2; // The string format sequence was 2 characters long
									break;
								}
								case 'd': // We're writing a signed int
								case 'i':
								case 'x': // We're writing a hexadecimal int
								case 'X':
								case 'u': // We're writing an unsigned int
								case 'o': // We're writing an octal int
								{
									Kernel::Driver::VGA::stdout.push((unsigned char*)&(format[last]), i - last); // Write the string so far

									// Write the string we found in the gap
									char str[sizeof(int) * 8 + 2]; // This string is the maximum size an int could possibly be

									int v = __builtin_va_arg(args, int);

									if (format[i + 1] == 'u') // Is it unsigned?
										v = Int::Abs(v);

									int base = (format[i + 1] == 'x' || format[i + 1] == 'X') ? 16 : ((format[i + 1] == 'o') ? 8 : 10); // Which base are we using?
									Int::ToStr(v, str, base); // Convert it to a string

									if (base == 16 && format[i + 1] == 'x') // Convert it to uppercase if we have to
									{
										for (int i = 0; str[i] != '\0'; i ++)
											str[i] = Char::ToLower(str[i]);
									}

									Kernel::Driver::VGA::stdout.push((unsigned char*)str, strlen(str)); // Write the inserted integer
									len += strlen(str);
									last = i + 2; // The integer format sequence was 2 characters long
									break;
								}
								case 'c':
								{
									Kernel::Driver::VGA::stdout.push((unsigned char*)&(format[last]), i - last); // Write the string so far

									// Write the character we found in the gap
									char character = (char)__builtin_va_arg(args, int);
									Kernel::Driver::VGA::stdout.push((unsigned char*)&character, 1); // Write the inserted character
									len ++;
									last = i + 2; // The character format sequence was 2 characters long
									break;
								}
								default:
									break;
							}
						}
						default:
							break;
					}

					len ++;
				}

				Kernel::Driver::VGA::stdout.push((unsigned char*)&(format[last]), i - last); // Write any trailing string

				__builtin_va_end(args);

				return Result<const char*>(format, STATUS_SUCCESS);
			}
		}
	}
}
