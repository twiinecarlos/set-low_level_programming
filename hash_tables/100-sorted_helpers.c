#include "hash_tables.h"
#include <stdlib.h>
#include <string.h>

/**
 * duplicate_string - duplicates a string
 * @string: string to duplicate
 *
 * Return: duplicated string
 */
char *duplicate_string(const char *string)
{
	char *copy;
	size_t length;

	length = strlen(string) + 1;

	copy = malloc(length);

	if (copy == NULL)
		return (NULL);

	strcpy(copy, string);

	return (copy);
}


/**
 * insert_sorted_node - inserts node in sorted linked list
 * @ht: sorted hash table
 * @node: node to insert
 *
 * Return: Nothing
 */
void insert_sorted_node(shash_table_t *ht, shash_node_t *node)
{
	shash_node_t *current;

	current = ht->shead;

	if (current == NULL)
	{
		ht->shead = node;
		ht->stail = node;
		return;
	}

	while (current != NULL && strcmp(current->key, node->key) < 0)
		current = current->snext;

	if (current == ht->shead)
	{
		node->snext = ht->shead;
		ht->shead->sprev = node;
		ht->shead = node;
	}
	else if (current == NULL)
	{
		node->sprev = ht->stail;
		ht->stail->snext = node;
		ht->stail = node;
	}
	else
	{
		node->snext = current;
		node->sprev = current->sprev;
		current->sprev->snext = node;
		current->sprev = node;
	}
}
