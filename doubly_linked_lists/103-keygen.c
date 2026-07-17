#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char charset[] = "A-CHRDw87lNS0E9B2TibgpnMVys5XzvtOGJcYLU+4mjW6fxqZeF3Qa1rPhdKIouk";

int f1(int len)
{
	return ((len ^ 0x3b) & 0x3f);
}

int f2(char *username, int len)
{
	int i, sum = 0;

	for (i = 0; i < len; i++)
		sum += (int)username[i];
	return ((sum ^ 0x4f) & 0x3f);
}

int f3(char *username, int len)
{
	int i, product = 1;

	for (i = 0; i < len; i++)
		product *= (int)username[i];
	return ((product ^ 0x55) & 0x3f);
}

int f4(char *username, int len)
{
	int i, max;

	max = (int)username[0];
	for (i = 0; i < len; i++)
	{
		if ((int)username[i] > max)
			max = (int)username[i];
	}
	srand(max ^ 0xe);
	return (rand() & 0x3f);
}

int f5(char *username, int len)
{
	int i, sum = 0;

	for (i = 0; i < len; i++)
		sum += (int)username[i] * (int)username[i];
	return ((sum ^ 0xef) & 0x3f);
}

int f6(int c)
{
	int i, val = 0;

	for (i = 0; c > i; i++)
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
	char *username;
	int len;
	char key[7];

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s username\n", argv[0]);
		exit(1);
	}

	username = argv[1];
	len = strlen(username);

	key[0] = charset[f1(len)];
	key[1] = charset[f2(username, len)];
	key[2] = charset[f3(username, len)];
	key[3] = charset[f4(username, len)];
	key[4] = charset[f5(username, len)];
	key[5] = charset[f6((int)(signed char)username[0])];
	key[6] = '\0';

	printf("%s\n", key);

	return (0);
}
