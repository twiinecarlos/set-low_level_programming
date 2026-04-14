#include "main.h"

/**
 * puts_half - prints second half of a string
 * @str: string to print
 */
void puts_half(char *str)
{
	int len = 0;
	int start;
	int i;

	/* find length */
	while (str[len] != '\0')
	{
		len++;
	}

	/* calculate starting point */
	if (len % 2 == 0)
	{
		start = len / 2;
	}
	else
	{
		start = (len - 1) / 2 + 1;
	}

	/* print from start */
	for (i = start; str[i] != '\0'; i++)
	{
		_putchar(str[i]);
	}

	_putchar('\n');
}
