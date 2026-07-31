#include "hash_tables.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * shash_table_create - creates a sorted hash table
 * @size: size of the table
 *
 * Return: pointer to hash table
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *ht;

	ht = malloc(sizeof(shash_table_t));
	if (ht == NULL)
		return (NULL);

	ht->array = calloc(size, sizeof(shash_node_t *));
	if (ht->array == NULL)
	{
		free(ht);
		return (NULL);
	}

	ht->size = size;
	ht->shead = NULL;
	ht->stail = NULL;

	return (ht);
}

/**
 * shash_table_set - adds key/value pair
 * @ht: hash table
 * @key: key
 * @value: value
 *
 * Return: 1 success, 0 failure
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	unsigned long int index;
	shash_node_t *node;

	if (ht == NULL || key == NULL || value == NULL)
		return (0);

	index = key_index((const unsigned char *)key, ht->size);

	node = malloc(sizeof(shash_node_t));
	if (node == NULL)
		return (0);

	node->key = duplicate_string(key);
	node->value = duplicate_string(value);

	if (node->key == NULL || node->value == NULL)
	{
		free(node->key);
		free(node->value);
		free(node);
		return (0);
	}

	node->next = ht->array[index];
	ht->array[index] = node;

	node->sprev = NULL;
	node->snext = NULL;

	insert_sorted_node(ht, node);

	return (1);
}

/**
 * shash_table_get - gets value
 * @ht: hash table
 * @key: key
 *
 * Return: value or NULL
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	unsigned long int index;
	shash_node_t *node;

	if (ht == NULL || key == NULL)
		return (NULL);

	index = key_index((const unsigned char *)key, ht->size);

	node = ht->array[index];

	while (node)
	{
		if (strcmp(node->key, key) == 0)
			return (node->value);

		node = node->next;
	}

	return (NULL);
}

/**
 * shash_table_print - prints hash table sorted
 * @ht: hash table
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *node;

	if (ht == NULL)
		return;

	printf("{");

	node = ht->shead;

	while (node)
	{
		printf("'%s': '%s'", node->key, node->value);

		if (node->snext)
			printf(", ");

		node = node->snext;
	}

	printf("}\n");
}

/**
 * shash_table_print_rev - prints reverse sorted
 * @ht: hash table
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *node;

	if (ht == NULL)
		return;

	printf("{");

	node = ht->stail;

	while (node)
	{
		printf("'%s': '%s'", node->key, node->value);

		if (node->sprev)
			printf(", ");

		node = node->sprev;
	}

	printf("}\n");
}
