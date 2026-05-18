#include "lists.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * print_listint_safe - prints a listint_t list safely
 * @head: pointer to head of list
 *
 * Return: number of nodes printed
 */
size_t print_listint_safe(const listint_t *head)
{
	const listint_t *current, *check;
	size_t count = 0;

	current = head;

	while (current != NULL)
	{
		check = head;

		while (check != current)
		{
			if (check == current->next)
			{
				printf("-> [%p] %d\n", (void *)current->next,
					current->next->n);
				return (count + 1);
			}

			check = check->next;
		}

		printf("[%p] %d\n", (void *)current, current->n);

		count++;
		current = current->next;
	}

	return (count);
}
