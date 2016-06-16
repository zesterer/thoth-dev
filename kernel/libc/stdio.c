#include "cstd/io.h"
#include "libc/string.h"

// Operations on files

// File access

// Formatted input/output

int printf(const char* format, ...)
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
						cstd_io_printn((char*)&(format[last]), i - last); // Write the string so far
						// Write the string we found in the gap
						char* str = __builtin_va_arg(args, char*);
						cstd_io_printn((char*)str, strlen(str)); // Write the inserted string
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
						cstd_io_printn((char*)&(format[last]), i - last); // Write the string so far

						// Write the string we found in the gap
						char str[sizeof(int) * 8 + 1]; // This string is the maximum size an int could possibly be

						int v = __builtin_va_arg(args, int);

						if (format[i + 1] == 'u') // Is it unsigned?
							v = abs(v);

						int base = (format[i + 1] == 'x' || format[i + 1] == 'X') ? 16 : ((format[i + 1] == 'o') ? 8 : 10); // Which base are we using?
						itoa(v, str, base); // Convert it to a string

						if (format[i + 1] == 'x') // Convert it to uppercase if we have to
						{
							for (int i = 0; str[i] != '\0'; i ++)
								str[i] = tolower(str[i]);
						}

						cstd_io_printn((char*)str, strlen(str)); // Write the inserted integer
						len += strlen(str);
						last = i + 2; // The integer format sequence was 2 characters long
						break;
					}
					case 'c':
					{
						cstd_io_printn((char*)&(format[last]), i - last); // Write the string so far

						// Write the character we found in the gap
						char character = (char)__builtin_va_arg(args, int);
						cstd_io_put((char)character); // Write the inserted character
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
	cstd_io_printn((char*)&(format[last]), i - last); // Write any trailing string

	__builtin_va_end(args);

	return len;
}
