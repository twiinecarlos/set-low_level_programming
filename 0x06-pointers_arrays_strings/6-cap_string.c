#include "main.h"

/**
 * cap_string - capitalizes all words of a string
 * @str: input string
 *
 * Return: pointer to str
 */
char *cap_string(char *str)
{
	int i = 0;
	int j;
	char sep[] = " \t\n,;.!?\"(){}";

	while (str[i] != '\0')
	{
		/* check if at start of string or after separator */
		if (i == 0)
		{
			if (str[i] >= 'a' && str[i] <= 'z')
				str[i] -= 32;
		}
		else
		{
			for (j = 0; sep[j] != '\0'; j++)
			{
				if (str[i - 1] == sep[j])
				{
					if (str[i] >= 'a' && str[i] <= 'z')
						str[i] -= 32;
				}
			}
		}
		i++;
	}

	return (str);
}
