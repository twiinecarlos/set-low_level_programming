#include "lists.h"
#include <stdlib.h>
#include <string.h>

/**
 * add_node - adds a new node at the beginning of a list_t list
 * @head: pointer to pointer to head of list
 * @str: string to duplicate and store in new node
 *
 * Return: address of new node, or NULL if failed
 */
list_t *add_node(list_t **head, const char *str)
{
	list_t *new;
	unsigned int len = 0;

	if (str == NULL)
		return (NULL);

	new = malloc(sizeof(list_t));
	if (new == NULL)
		return (NULL);

	new->str = strdup(str);
	if (new->str == NULL)
	{
		free(new);
		return (NULL);
	}

	while (str[len] != '\0')
		len++;

	new->len = len;
	new->next = *head;
	*head = new;

	return (new);
}
