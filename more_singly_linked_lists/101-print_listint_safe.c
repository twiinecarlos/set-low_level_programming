#include "lists.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * print_listint_safe - prints a listint_t list safely (even with loops)
 * @head: pointer to list
 *
 * Return: number of nodes printed
 */
size_t print_listint_safe(const listint_t *head)
{
    const listint_t **seen;
    size_t i = 0, count = 0;
    const listint_t *current = head;

    seen = malloc(sizeof(listint_t *) * 1024 * 1024);
    if (seen == NULL)
        exit(98);

    while (current != NULL)
    {
        for (i = 0; i < count; i++)
        {
            if (seen[i] == current)
            {
                printf("-> [%p] %d\n", (void *)current, current->n);
                free(seen);
                return (count);
            }
        }

        seen[count] = current;
        printf("[%p] %d\n", (void *)current, current->n);
        count++;

        current = current->next;
    }

    free(seen);
    return (count);
}
