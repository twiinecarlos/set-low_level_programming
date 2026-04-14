#include "main.h"

/**
 * rev_string - reverses a string in place
 * @s: pointer to string
 */
void rev_string(char *s)
{
	int i = 0;
	int j;
	char temp;

	/* find length */
	while (s[i] != '\0')
	{
		i++;
	}

	j = i - 1;

	/* swap characters */
	i = 0;
	while (i < j)
	{
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;

		i++;
		j--;
	}
}
