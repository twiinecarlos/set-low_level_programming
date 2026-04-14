#include "main.h"

/* helper function */
int find_sqrt(int n, int i);

/**
 * _sqrt_recursion - returns natural square root of a number
 * @n: number
 *
 * Return: square root or -1
 */
int _sqrt_recursion(int n)
{
	if (n < 0)
	{
		return (-1);
	}

	return (find_sqrt(n, 1));
}

/**
 * find_sqrt - finds square root recursively
 * @n: number
 * @i: current guess
 *
 * Return: square root or -1
 */
int find_sqrt(int n, int i)
{
	if (i * i == n)
	{
		return (i);
	}

	if (i * i > n)
	{
		return (-1);
	}

	return (find_sqrt(n, i + 1));
}
