#include "cstd/conv.h"

int abs(int n)
{
	return n < 0 ? -n : n;
}

/* Pseudo-random sequence generation */

static unsigned long next_rand = 1;

int rand()
{
	next_rand = next_rand * 1103515245 + 12345;
	return (unsigned long)(next_rand / 65536) % 32768;
}

void srand(unsigned int seed)
{
	next_rand = seed;
}

int cstd_conv_str_to_int(const char* str)
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

char* cstd_conv_int_to_str(int value, char* str, int base)
{
	long v = 1;
	int i = 0;

	if (base < 2 || base > 32)
		return str;

	if (value < 0 && base == 10)
	{
		str[i] = '-';
		i ++;
	}

	value = abs(value);

	while (v < ((long)1 << (sizeof(int) * 8 - 1)))
		v *= base;

	while (v > 0)
	{
		if (value / v > 0)
		{
			if ((value / v) % base > 9)
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
