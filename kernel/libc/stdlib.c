#include "libc/stdlib.h"

/* String conversion */

int atoi(const char* str)
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

char* itoa(int value, char* str, int base)
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

	while (v < ((long)1 << (sizeof(int) * 8)))
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
