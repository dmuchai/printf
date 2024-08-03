#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * @k: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precsion: precsion specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char k, char buffer[],
	int flags, int width, int precsion, int size)
{
	int i = 0;
	char padd = ' ';

	UNUSED(precsion);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[i++] = k;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * writ_num - Prints a string
 * @iz_negtive: lsta of arguments
 * @indx: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precsion: precsion specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int writ_num(int iz_negtive, int indx, char buffer[],
	int flags, int width, int precsion, int size)
{
	int length = BUFF_SIZE - indx - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (iz_negtive)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(indx, buffer, flags, width, precsion,
		length, padd, extra_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @indx: indxex at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @prec: precsion specifier
 * @length: Number length
 * @padd: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int indx, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && indx == BUFF_SIZE - 2 && buffer[indx] == '0' && width == 0)
		return (0);
	if (prec == 0 && indx == BUFF_SIZE - 2 && buffer[indx] == '0')
		buffer[indx] = padd = ' ';
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--indx] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--indx] = extra_c;
			return (write(1, &buffer[indx], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--indx] = extra_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[indx], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[indx], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--indx] = extra_c;
	return (write(1, &buffer[indx], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @iz_negtive: Number indxicating if the num is negative
 * @indx: indxex at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precsion: precsion specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int iz_negtive, int indx,
	char buffer[],
	int flags, int width, int precsion, int size)
{
	int length = BUFF_SIZE - indx - 1, i = 0;
	char padd = ' ';

	UNUSED(iz_negtive);
	UNUSED(size);

	if (precsion == 0 && indx == BUFF_SIZE - 2 && buffer[indx] == '0')
		return (0);

	if (precsion > 0 && precsion < length)
		padd = ' ';

	while (precsion > length)
	{
		buffer[--indx] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[indx], length) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[indx], length));
		}
	}

	return (write(1, &buffer[indx], length));
}

/**
 * write_pointer - Write a memory address
 * @buffer: Arrays of chars
 * @indx: indxex at which the number starts in the buffer
 * @length: Length of number
 * @width: Wwidth specifier
 * @flags: Flags specifier
 * @padd: Char representing the padding
 * @extra_c: Char representing extra char
 * @padd_start: indxex at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int indx, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			buffer[--indx] = 'x';
			buffer[--indx] = '0';
			if (extra_c)
				buffer[--indx] = extra_c;
			return (write(1, &buffer[indx], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			buffer[--indx] = 'x';
			buffer[--indx] = '0';
			if (extra_c)
				buffer[--indx] = extra_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[indx], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[indx], length - (1 - padd_start) - 2));
		}
	}
	buffer[--indx] = 'x';
	buffer[--indx] = '0';
	if (extra_c)
		buffer[--indx] = extra_c;
	return (write(1, &buffer[indx], BUFF_SIZE - indx - 1));
}
