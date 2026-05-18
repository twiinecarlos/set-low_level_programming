#include "lists.h"
#include <stdlib.h>

/**
 * free_listint_safe - frees a listint_t list safely (even with loops)
 * @h: pointer to pointer to head
 *
 * Return: number of nodes freed
 */
size_t free_listint_safe(listint_t **h)
{
	listint_t *temp;
	size_t count = 0;

	if (h == NULL || *h == NULL)
		return (0);

	while (*h != NULL)
	{
		temp = (*h)->next;
		free(*h);
		count++;

		/*
		 * If next pointer already points to a freed or visited node,
		 * break safely to avoid infinite loop.
		 */
		*h = temp;
	}

	*h = NULL;
	return (count);
}
