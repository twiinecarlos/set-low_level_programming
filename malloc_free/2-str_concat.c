#include "main.h"
#include <stdlib.h>

/**
 * str_concat - concatenates two strings into a new memory space
 * @s1: first string
 * @s2: second string
 *
 * Return: pointer to newly allocated concatenated string,
 *         or NULL on failure
 */
char *str_concat(char *s1, char *s2)
{
	char *new_str;
	int i = 0, j = 0;
	int len1 = 0, len2 = 0;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";

	while (s1[len1] != '\0')
		len1++;

	while (s2[len2] != '\0')
		len2++;

	new_str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (new_str == NULL)
		return (NULL);

	while (i < len1)
	{
		new_str[i] = s1[i];
		i++;
	}

	while (j < len2)
	{
		new_str[i] = s2[j];
		i++;
		j++;
	}

	new_str[i] = '\0';

	return (new_str);
}
