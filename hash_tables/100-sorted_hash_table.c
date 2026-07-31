#include "hash_tables.h"
#include <stdio.h>
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
	unsigned int len;

	if (string == NULL)
		return (NULL);

	len = strlen(string) + 1;
	copy = malloc(sizeof(char) * len);

	if (copy == NULL)
		return (NULL);

	strcpy(copy, string);

	return (copy);
}

/**
 * insert_sorted_node - inserts node into sorted list
 * @ht: sorted hash table
 * @node: node to insert
 *
 * Return: void
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

	node->sprev = current;
	node->snext = NULL;
	current->snext = node;
	ht->stail = node;
}

/**
 * shash_table_create - creates sorted hash table
 * @size: size of table
 *
 * Return: pointer to new table
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
 * Return: 1 on success, 0 on failure
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	unsigned long int index;
	shash_node_t *node;

	if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
		return (0);

	index = key_index((const unsigned char *)key, ht->size);

	node = ht->array[index];

	while (node)
	{
		if (strcmp(node->key, key) == 0)
		{
			free(node->value);
			node->value = duplicate_string(value);

			if (node->value == NULL)
				return (0);

			return (1);
		}

		node = node->next;
	}

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
 * shash_table_print - prints sorted table
 * @ht: hash table
 *
 * Return: void
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
 * shash_table_print_rev - prints reverse sorted table
 * @ht: hash table
 *
 * Return: void
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

/**
 * shash_table_delete - deletes hash table
 * @ht: hash table
 *
 * Return: void
 */
void shash_table_delete(shash_table_t *ht)
{
	unsigned long int i;
	shash_node_t *node;
	shash_node_t *temp;

	if (ht == NULL)
		return;

	for (i = 0; i < ht->size; i++)
	{
		node = ht->array[i];

		while (node)
		{
			temp = node->next;

			free(node->key);
			free(node->value);
			free(node);

			node = temp;
		}
	}

	free(ht->array);
	free(ht);
}
