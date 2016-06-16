#include "cstd/io.h"
#include "cstd/str.h"

#if defined(THOTH_ARCH_i686) || defined(THOTH_ARCH_x86_64)
	#include "thoth/vga.h"
#endif

static bool char_is_hex(char c);
static uint8_t char_to_hex(char c);

void cstd_io_put(char c)
{
	#if defined(THOTH_ARCH_i686) || defined(THOTH_ARCH_x86_64)
		thoth_vga_putc(c);
	#else
		// Do nothing
	#endif
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

void cstd_io_print(const char* str)
{
	size_t len = cstd_str_length(str);

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
						thoth_vga_set_color(char_to_hex(str[i + 2]), thoth_vga_terminal_color >> 4);
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
						thoth_vga_set_color(thoth_vga_terminal_color & 0xF, char_to_hex(str[i + 2]));
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
				thoth_vga_putc(str[i]);
			#else
				// Do nothing
			#endif
		}
	}
}
