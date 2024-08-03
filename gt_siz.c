#include "main.h"

/**
 * gt_siz - Calculates the size to cast the argument
 * @formt: formatted string in which to print the arguments
 * @i: lst of arguments to be printed.
 *
 * Return: precsion.
 */
int gt_siz(const char *formt, int *i)
{
	int curr_i = *i + 1;
	int size = 0;

	if (formt[curr_i] == 'l')
		size = S_LONG;
	else if (formt[curr_i] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = curr_i - 1;
	else
		*i = curr_i;

	return (size);
}
