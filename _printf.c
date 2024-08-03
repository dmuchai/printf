#include "main.h"

void print_buffer(char buffer[], int *buff_indx);

/**
 * _printf - Printf function
 * @formt: formt specs.
 * Return: Printed chars.
 */
int _printf(const char *formt, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precsion, size, buff_indx = 0;
	va_list lst;
	char buffer[BUFF_SIZE];

	if (formt == NULL)
		return (-1);

	va_start(lst, formt);

	for (i = 0; formt && formt[i] != '\0'; i++)
	{
		if (formt[i] != '%')
		{
			buffer[buff_indx++] = formt[i];
			if (buff_indx == BUFF_SIZE)
				print_buffer(buffer, &buff_indx);
			/* write(1, &formt[i], 1);*/
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_indx);
			flags = gt_flgs(formt, &i);
			width = gt_wdth(formt, &i, lst);
			precsion = get_exact(formt, &i, lst);
			size = gt_siz(formt, &i);
			++i;
			printed = format_handler(formt, &i, lst, buffer,
				flags, width, precsion, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_indx);

	va_end(lst);

	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_indx: index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_indx)
{
	if (*buff_indx > 0)
		write(1, &buffer[0], *buff_indx);

	*buff_indx = 0;
}
