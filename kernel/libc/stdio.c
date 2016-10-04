#include "libc/stdio.h"
#include "libc/stdlib.h"
#include "libc/string.h"
#include "libc/ctype.h"

#if defined(THOTH_ARCH_i686) || defined(THOTH_ARCH_x86_64)
	#include "thoth/vga.h"
#endif

#include "thoth/kernel/driver/vga/vga.hpp"

#include "stdbool.h"

static bool char_is_hex(char c);
static uint8_t char_to_hex(char c);
static int putsn(const char* str, size_t len);

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
						putsn((char*)&(format[last]), i - last); // Write the string so far
						// Write the string we found in the gap
						char* str = __builtin_va_arg(args, char*);
						putsn((char*)str, strlen(str)); // Write the inserted string
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
						putsn((char*)&(format[last]), i - last); // Write the string so far

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

						putsn((char*)str, strlen(str)); // Write the inserted integer
						len += strlen(str);
						last = i + 2; // The integer format sequence was 2 characters long
						break;
					}
					case 'c':
					{
						putsn((char*)&(format[last]), i - last); // Write the string so far

						// Write the character we found in the gap
						char character = (char)__builtin_va_arg(args, int);
						putchar((char)character); // Write the inserted character
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
	putsn((char*)&(format[last]), i - last); // Write any trailing string

	__builtin_va_end(args);

	return len;
}

// Character input/output

int putchar(int character)
{
	#if defined(THOTH_ARCH_i686) || defined(THOTH_ARCH_x86_64)
		Thoth::Kernel::Driver::VGA::PutChar((char)character);
	#else
		// Do nothing
	#endif

	return 0;
}

static bool char_is_hex(char c)
{
	if (c >= '0' && c <= '9') return true;
	if (c >= 'a' && c <= 'z') return true;
	if (c >= 'A' && c <= 'Z') return true;
	return false;
}

static uint8_t char_to_hex(char c)
{
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'a' && c <= 'f') return 10 + c - 'a';
	if (c >= 'A' && c <= 'F') return 10 + c - 'A';
	return 0;
}

int puts(const char* str)
{
	return putsn(str, strlen(str));
}

static int putsn(const char* str, size_t len)
{
	for (size_t i = 0; i < len; i ++)
	{
		int16_t escaped = 0;

		if (str[i] == '$' && i + 1 < len)
		{
			if (escaped == 0 && str[i + 1] == 'F' && i + 2 < len)
			{
				if (char_is_hex(str[i + 2]))
				{
					escaped = 1;

					#if defined(THOTH_ARCH_x86_64) || defined(THOTH_ARCH_i686)
						Thoth::Kernel::Driver::VGA::SetColour((Thoth::Kernel::Driver::VGA::Colour)char_to_hex(str[i + 2]), (Thoth::Kernel::Driver::VGA::Colour)(Thoth::Kernel::Driver::VGA::cursor_colour >> 4));
					#else
						// Do nothing
					#endif

					i += 2;
				}
			}

			if (escaped == 0 && str[i + 1] == 'B' && i + 2 < len)
			{
				if (char_is_hex(str[i + 2]))
				{
					escaped = 1;

					#if defined(THOTH_ARCH_x86_64) || defined(THOTH_ARCH_i686)
						Thoth::Kernel::Driver::VGA::SetColour((Thoth::Kernel::Driver::VGA::Colour)(Thoth::Kernel::Driver::VGA::cursor_colour & 0xF), (Thoth::Kernel::Driver::VGA::Colour)char_to_hex(str[i + 2]));
					#else
						// Do nothing
					#endif

					i += 2;
				}
			}
		}

		if (escaped != 1)
		{
			#if defined(THOTH_ARCH_x86_64) || defined(THOTH_ARCH_i686)
				Thoth::Kernel::Driver::VGA::PutChar(str[i]);
			#else
				// Do nothing
			#endif
		}
	}

	return 0;
}
