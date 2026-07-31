#include "hash_tables.h"
#include <stdlib.h>

/**
 * shash_table_delete - deletes a sorted hash table
 * @ht: sorted hash table to delete
 *
 * Return: Nothing
 */
void shash_table_delete(shash_table_t *ht)
{
	shash_node_t *node;
	shash_node_t *next;

	if (ht == NULL)
		return;

	node = ht->shead;

	while (node != NULL)
	{
		next = node->snext;

		free(node->key);
		free(node->value);
		free(node);

		node = next;
	}

	free(ht->array);
	free(ht);
}
