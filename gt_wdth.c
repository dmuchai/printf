#include "main.h"

/**
 * gt_wdth - Calculates the width for printing
 * @formt: formtted string in which to print the arguments.
 * @i: lst of arguments to be printed.
 * @lst: lst of arguments.
 *
 * Return: width.
 */
int gt_wdth(const char *formt, int *i, va_list lst)
{
	int curr_i;
	int width = 0;

	for (curr_i = *i + 1; formt[curr_i] != '\0'; curr_i++)
	{
		if (iz_digit(formt[curr_i]))
		{
			width *= 10;
			width += formt[curr_i] - '0';
		}
		else if (formt[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(lst, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (width);
}
