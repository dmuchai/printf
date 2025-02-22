#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * miprint_char - Prints a char
 * @types: lst a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width
 * @precsion: precsion specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int miprint_char(va_list types, char buffer[],
	int flags, int width, int precsion, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precsion, size));
}
/************************* PRINT A STRING *************************/
/**
 * miprint_string - Prints a string
 * @types: lst a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precsion: precsion specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int miprint_string(va_list types, char buffer[],
	int flags, int width, int precsion, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precsion);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precsion >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precsion >= 0 && precsion < length)
		length = precsion;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * miprint_percent - Prints a percent sign
 * @types: lsta of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precsion: precsion specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int miprint_percent(va_list types, char buffer[],
	int flags, int width, int precsion, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precsion);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * miprint_int - Print int
 * @types: lsta of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precsion: precsion specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int miprint_int(va_list types, char buffer[],
	int flags, int width, int precsion, int size)
{
	int i = BUFF_SIZE - 2;
	int iz_negtive = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		iz_negtive = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (writ_num(iz_negtive, i, buffer, flags, width, precsion, size));
}

/************************* PRINT BINARY *************************/
/**
 * miprint_binary - Prints an unsigned number
 * @types: lsta of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precsion: precsion specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int miprint_binary(va_list types, char buffer[],
	int flags, int width, int precsion, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precsion);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
