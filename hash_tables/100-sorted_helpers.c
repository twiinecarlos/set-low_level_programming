#include "hash_tables.h"
#include <stdlib.h>
#include <string.h>

/**
 * duplicate_string - duplicates string
 * @string: string
 *
 * Return: duplicated string
 */
char *duplicate_string(const char *string)
{
	char *copy;
	unsigned int len;

	len = strlen(string) + 1;

	copy = malloc(len);

	if (copy == NULL)
		return (NULL);

	memcpy(copy, string, len);

	return (copy);
}


/**
 * insert_sorted_node - inserts node in sorted list
 * @ht: sorted hash table
 * @node: node
 */
void insert_sorted_node(shash_table_t *ht, shash_node_t *node)
{
	shash_node_t *current;

	if (ht->shead == NULL)
	{
		ht->shead = node;
		ht->stail = node;
		return;
	}

	current = ht->shead;

	while (current)
	{
		if (strcmp(node->key, current->key) < 0)
		{
			node->snext = current;
			node->sprev = current->sprev;

			if (current->sprev)
				current->sprev->snext = node;
			else
				ht->shead = node;

			current->sprev = node;
			return;
		}

		if (current->snext == NULL)
			break;

		current = current->snext;
	}

	node->sprev = ht->stail;
	ht->stail->snext = node;
	ht->stail = node;
}
