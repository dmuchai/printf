#include "main.h"
/**
 * format_handler - Fctn prints an argument based on its type
 * @fmt: formtted string in which to print the arguments.
 * @lst: lst of arguments to be printed.
 * @indx: indx.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precsion: precsion specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int format_handler(const char *fmt, int *indx, va_list lst, char buffer[],
	int flags, int width, int precsion, int size)
{
	int i, unknow_len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', miprint_char}, {'s', miprint_string}, {'%', miprint_percent},
		{'i', miprint_int}, {'d', miprint_int}, {'b', miprint_binary},
		{'u', myprindx_unsigned}, {'o', myprindx_octa}, {'x', myprindx_hexdeci},
		{'X', myprindx_hex_upp}, {'p', myprindx_point}, {'S', myprindx_non_print},
		{'r', myprindx_rev}, {'R', myprindx_rot13string}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*indx] == fmt_types[i].fmt)
			return (fmt_types[i].fn(lst, buffer, flags, width, precsion, size));

	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*indx] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*indx - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*indx);
			while (fmt[*indx] != ' ' && fmt[*indx] != '%')
				--(*indx);
			if (fmt[*indx] == ' ')
				--(*indx);
			return (1);
		}
		unknow_len += write(1, &fmt[*indx], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
