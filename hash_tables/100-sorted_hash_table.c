#include "hash_tables.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * duplicate_string - duplicates a string
 * @string: string to duplicate
 *
 * Return: Pointer to the duplicated string, or NULL on failure
 */
static char *duplicate_string(const char *string)
{
	char *copy;
	size_t length;

	length = strlen(string) + 1;
	copy = malloc(length);
	if (copy == NULL)
		return (NULL);

	memcpy(copy, string, length);
	return (copy);
}

/**
 * insert_sorted_node - inserts a node into the sorted linked list
 * @ht: sorted hash table
 * @node: node to insert
 */
static void insert_sorted_node(shash_table_t *ht, shash_node_t *node)
{
	shash_node_t *current;

	if (ht->shead == NULL)
	{
		ht->shead = node;
		ht->stail = node;
		return;
	}

	if (strcmp(node->key, ht->shead->key) < 0)
	{
		node->snext = ht->shead;
		ht->shead->sprev = node;
		ht->shead = node;
		return;
	}

	current = ht->shead;

	while (current->snext != NULL &&
	       strcmp(node->key, current->snext->key) > 0)
	{
		current = current->snext;
	}

	node->sprev = current;
	node->snext = current->snext;

	if (current->snext != NULL)
		current->snext->sprev = node;
	else
		ht->stail = node;

	current->snext = node;
}

/**
 * shash_table_create - creates a sorted hash table
 * @size: size of the hash table
 *
 * Return: Pointer to the newly created hash table, or NULL on failure
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *table;

	if (size == 0)
		return (NULL);

	table = malloc(sizeof(shash_table_t));
	if (table == NULL)
		return (NULL);

	table->array = calloc(size, sizeof(shash_node_t *));
	if (table->array == NULL)
	{
		free(table);
		return (NULL);
	}

	table->size = size;
	table->shead = NULL;
	table->stail = NULL;

	return (table);
}

/**
 * shash_table_set - adds or updates an element in a sorted hash table
 * @ht: sorted hash table
 * @key: key of the element
 * @value: value associated with the key
 *
 * Return: 1 on success, or 0 on failure
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	unsigned long int index;
	shash_node_t *current;
	shash_node_t *new_node;
	char *new_value;

	if (ht == NULL || ht->array == NULL || ht->size == 0 ||
	    key == NULL || *key == '\0' || value == NULL)
		return (0);

	index = key_index((const unsigned char *)key, ht->size);
	current = ht->array[index];

	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
		{
			new_value = duplicate_string(value);
			if (new_value == NULL)
				return (0);

			free(current->value);
			current->value = new_value;
			return (1);
		}

		current = current->next;
	}

	new_node = malloc(sizeof(shash_node_t));
	if (new_node == NULL)
		return (0);

	new_node->key = duplicate_string(key);
	if (new_node->key == NULL)
	{
		free(new_node);
		return (0);
	}

	new_node->value = duplicate_string(value);
	if (new_node->value == NULL)
	{
		free(new_node->key);
		free(new_node);
		return (0);
	}

	new_node->next = ht->array[index];
	new_node->sprev = NULL;
	new_node->snext = NULL;
	ht->array[index] = new_node;

	insert_sorted_node(ht, new_node);

	return (1);
}

/**
 * shash_table_get - retrieves a value associated with a key
 * @ht: sorted hash table
 * @key: key to search for
 *
 * Return: Associated value, or NULL if the key was not found
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	unsigned long int index;
	shash_node_t *current;

	if (ht == NULL || ht->array == NULL || ht->size == 0 ||
	    key == NULL || *key == '\0')
		return (NULL);

	index = key_index((const unsigned char *)key, ht->size);
	current = ht->array[index];

	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
			return (current->value);

		current = current->next;
	}

	return (NULL);
}

/**
 * shash_table_print - prints a sorted hash table
 * @ht: sorted hash table
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *current;
	int separator;

	if (ht == NULL)
		return;

	current = ht->shead;
	separator = 0;

	printf("{");

	while (current != NULL)
	{
		if (separator)
			printf(", ");

		printf("'%s': '%s'", current->key, current->value);
		separator = 1;
		current = current->snext;
	}

	printf("}\n");
}

/**
 * shash_table_print_rev - prints a sorted hash table in reverse order
 * @ht: sorted hash table
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *current;
	int separator;

	if (ht == NULL)
		return;

	current = ht->stail;
	separator = 0;

	printf("{");

	while (current != NULL)
	{
		if (separator)
			printf(", ");

		printf("'%s': '%s'", current->key, current->value);
		separator = 1;
		current = current->sprev;
	}

	printf("}\n");
}

/**
 * shash_table_delete - deletes a sorted hash table
 * @ht: sorted hash table to delete
 */
void shash_table_delete(shash_table_t *ht)
{
	unsigned long int index;
	shash_node_t *current;
	shash_node_t *next;

	if (ht == NULL)
		return;

	for (index = 0; index < ht->size; index++)
	{
		current = ht->array[index];

		while (current != NULL)
		{
			next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			current = next;
		}
	}

	free(ht->array);
	free(ht);
}
