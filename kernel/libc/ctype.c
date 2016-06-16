#include "libc/ctype.h"

// Character conversion functions
int toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return 'A' - 'a' + c;
	return c;
}

int tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return 'a' - 'A' + c;
	return c;
}
