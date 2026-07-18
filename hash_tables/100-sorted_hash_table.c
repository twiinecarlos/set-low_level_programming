#include "hash_tables.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
 * shash_table_set - adds an element to sorted hash table
 * @ht: hash table
 * @key: key
 * @value: value
 *
 * Return: 1 on success, 0 on failure
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	shash_node_t *new;
	shash_node_t *current;

	if (ht == NULL || key == NULL || value == NULL)
		return (0);

	new = malloc(sizeof(shash_node_t));
	if (new == NULL)
		return (0);

	new->key = strdup(key);
	new->value = strdup(value);

	if (new->key == NULL || new->value == NULL)
	{
		free(new->key);
		free(new->value);
		free(new);
		return (0);
	}

	new->next = NULL;
	new->sprev = NULL;
	new->snext = NULL;

	current = ht->shead;

	while (current)
	{
		if (strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = strdup(value);
			free(new->key);
			free(new->value);
			free(new);
			return (1);
		}

		current = current->snext;
	}

	if (ht->shead == NULL)
	{
		ht->shead = new;
		ht->stail = new;
	}
	else
	{
		current = ht->shead;

		while (current && strcmp(current->key, key) < 0)
			current = current->snext;

		if (current == ht->shead)
		{
			new->snext = ht->shead;
			ht->shead->sprev = new;
			ht->shead = new;
		}
		else if (current == NULL)
		{
			new->sprev = ht->stail;
			ht->stail->snext = new;
			ht->stail = new;
		}
		else
		{
			new->snext = current;
			new->sprev = current->sprev;
			current->sprev->snext = new;
			current->sprev = new;
		}
	}

	return (1);
}

/**
 * shash_table_get - gets value from hash table
 * @ht: hash table
 * @key: key
 *
 * Return: value or NULL
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	shash_node_t *current;

	if (ht == NULL || key == NULL)
		return (NULL);

	current = ht->shead;

	while (current)
	{
		if (strcmp(current->key, key) == 0)
			return (current->value);

		current = current->snext;
	}

	return (NULL);
}

/**
 * shash_table_print - prints sorted hash table
 * @ht: hash table
 *
 * Return: void
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *current;
	int first = 1;

	if (ht == NULL)
		return;

	printf("{");

	current = ht->shead;

	while (current)
	{
		if (!first)
			printf(", ");

		printf("'%s': '%s'", current->key, current->value);
		first = 0;

		current = current->snext;
	}

	printf("}\n");
}

/**
 * shash_table_print_rev - prints reverse sorted hash table
 * @ht: hash table
 *
 * Return: void
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *current;
	int first = 1;

	if (ht == NULL)
		return;

	printf("{");

	current = ht->stail;

	while (current)
	{
		if (!first)
			printf(", ");

		printf("'%s': '%s'", current->key, current->value);
		first = 0;

		current = current->sprev;
	}

	printf("}\n");
}

/**
 * shash_table_delete - deletes sorted hash table
 * @ht: hash table
 *
 * Return: void
 */
void shash_table_delete(shash_table_t *ht)
{
	shash_node_t *current;
	shash_node_t *temp;

	if (ht == NULL)
		return;

	current = ht->shead;

	while (current)
	{
		temp = current->snext;

		free(current->key);
		free(current->value);
		free(current);

		current = temp;
	}

	free(ht->array);
	free(ht);
}
