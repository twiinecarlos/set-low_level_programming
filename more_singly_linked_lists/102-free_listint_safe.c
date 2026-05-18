#include "lists.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * free_listint_safe - frees a listint_t list safely (even with loops)
 * @h: pointer to head pointer
 *
 * Return: number of nodes freed
 */
size_t free_listint_safe(listint_t **h)
{
	const listint_t *seen[1024];
	listint_t *tmp;
	size_t i, count = 0;

	if (h == NULL)
		return (0);

	while (*h != NULL)
	{
		for (i = 0; i < count; i++)
		{
			if (seen[i] == *h)
			{
				*h = NULL;
				return (count);
			}
		}

		seen[count] = *h;
		tmp = (*h)->next;
		free(*h);
		*h = tmp;
		count++;
	}

	*h = NULL;
	return (count);
}
