#include "hash_tables.h"
#include <stdlib.h>

/**
 * shash_table_delete - deletes sorted hash table
 * @ht: sorted hash table
 */
void shash_table_delete(shash_table_t *ht)
{
	shash_node_t *node;
	shash_node_t *next;

	if (ht == NULL)
		return;

	node = ht->shead;

	while (node)
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
