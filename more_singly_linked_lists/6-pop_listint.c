#include "lists.h"
#include <stdlib.h>

/**
 * pop_listint - deletes the head node of a listint_t linked list
 * @head: pointer to pointer to head of list
 *
 * Return: the data (n) of the deleted node, or 0 if list is empty
 */
int pop_listint(listint_t **head)
{
	listint_t *temp;
	int value;

	if (head == NULL || *head == NULL)
		return (0);

	temp = *head;
	value = temp->n;
	*head = temp->next;
	free(temp);

	return (value);
}
