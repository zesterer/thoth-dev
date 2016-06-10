#include "cstd/str.h"

size_t cstd_str_length(const char* str)
{
	int i;
	for (i = 0; str[i] != 0; i ++) { }
	
	return i;
}

char* cstd_str_copy(const char* src, char* dest)
{
	size_t i = 0;
	do
	{
		dest[i] = src[i];
		i ++;
	}
	while (src[i] != 0);

	return dest;
}

char* cstd_str_copy_n(const char* src, char* dest, size_t n)
{
	size_t i = 0;
	do
	{
		if (i >= n)
			break;
		dest[i] = src[i];
		i ++;
	}
	while (src[i] != 0);

	return dest;
}

char* cstd_str_find(const char* str, char val)
{
	for (int i = 0; str[i] != 0; i ++)
	{
		if (str[i] == val)
			return &str[i];
	}

	return NULL;
}
