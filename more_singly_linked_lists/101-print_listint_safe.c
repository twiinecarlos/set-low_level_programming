#include "lists.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * print_listint_safe - prints a listint_t list safely (handles loops)
 * @head: pointer to list
 *
 * Return: number of nodes printed
 */
size_t print_listint_safe(const listint_t *head)
{
	const listint_t *nodes[1024];
	size_t i = 0, count = 0;
	const listint_t *current = head;

	while (current != NULL)
	{
		for (i = 0; i < count; i++)
		{
			if (nodes[i] == current)
			{
				printf("-> [%p] %d\n", (void *)current, current->n);
				return (count);
			}
		}

		nodes[count] = current;
		printf("[%p] %d\n", (void *)current, current->n);
		count++;

		current = current->next;
	}

	return (count);
}
