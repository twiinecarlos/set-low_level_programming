#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * compute_index - computes one index (0-63) into the key charset,
 * using one of six algorithms selected by mode, matching the
 * behaviour of the original crackme5 binary
 * @username: the username string
 * @len: length of the username
 * @mode: which algorithm to run (1 through 6)
 *
 * Return: an index between 0 and 63
 */
int compute_index(char *username, int len, int mode)
{
	int i, sum, product, max, val, c;

	if (mode == 1)
		return ((len ^ 0x3b) & 0x3f);
	if (mode == 2)
	{
		for (sum = 0, i = 0; i < len; i++)
			sum += (int)username[i];
		return ((sum ^ 0x4f) & 0x3f);
	}
	if (mode == 3)
	{
		for (product = 1, i = 0; i < len; i++)
			product *= (int)username[i];
		return ((product ^ 0x55) & 0x3f);
	}
	if (mode == 4)
	{
		for (max = (int)username[0], i = 0; i < len; i++)
			if ((int)username[i] > max)
				max = (int)username[i];
		srand(max ^ 0xe);
		return (rand() & 0x3f);
	}
	if (mode == 5)
	{
		for (sum = 0, i = 0; i < len; i++)
			sum += (int)username[i] * (int)username[i];
		return ((sum ^ 0xef) & 0x3f);
	}
	c = (int)(signed char)username[0];
	for (val = 0, i = 0; c > i; i++)
		val = rand();
	return ((val ^ 0xe5) & 0x3f);
}

/**
 * main - generates a valid key for crackme5 given a username
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char charset[] =
		"A-CHRDw87lNS0E9B2TibgpnMVys5XzvtOGJcYLU+4mjW6fxqZeF3Qa1rPhdKIouk";
	char *username;
	int len, mode;
	char key[7];

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s username\n", argv[0]);
		exit(1);
	}

	username = argv[1];
	len = strlen(username);

	for (mode = 1; mode <= 6; mode++)
		key[mode - 1] = charset[compute_index(username, len, mode)];
	key[6] = '\0';

	printf("%s\n", key);

	return (0);
}
