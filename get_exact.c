#include "main.h"

/**
 * get_exact - Calculates the precsion for printing
 * @formt: formatted string in which to print the arguments
 * @i: lst of arguments to be printed.
 * @lst: lst of arguments.
 *
 * Return: precsion.
 */
int get_exact(const char *formt, int *i, va_list lst)
{
	int curr_i = *i + 1;
	int precsion = -1;

	if (formt[curr_i] != '.')
		return (precsion);

	precsion = 0;

	for (curr_i += 1; formt[curr_i] != '\0'; curr_i++)
	{
		if (iz_digit(formt[curr_i]))
		{
			precsion *= 10;
			precsion += formt[curr_i] - '0';
		}
		else if (formt[curr_i] == '*')
		{
			curr_i++;
			precsion = va_arg(lst, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (precsion);
}
