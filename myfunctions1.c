#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * myprindx_unsigned - Prints an unsigned number
 * @types: lst a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precsion: precsion specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int myprindx_unsigned(va_list types, char buffer[],
	int flags, int width, int precsion, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precsion, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * myprindx_octa - Prints an unsigned number in octal notation
 * @types: lsta of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precsion: precsion specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int myprindx_octa(va_list types, char buffer[],
	int flags, int width, int precsion, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precsion, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * myprindx_hexdeci - Prints an unsigned number in hexadecimal notation
 * @types: lsta of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precsion: precsion specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int myprindx_hexdeci(va_list types, char buffer[],
	int flags, int width, int precsion, int size)
{
	return (myprindx_hex(types, "0123456789abcdef", buffer,
		flags, 'x', width, precsion, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * myprindx_hex_upp - Prints an unsigned number in upper hexadecimal notation
 * @types: lsta of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precsion: precsion specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int myprindx_hex_upp(va_list types, char buffer[],
	int flags, int width, int precsion, int size)
{
	return (myprindx_hex(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precsion, size));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * myprindx_hex - Prints a hexadecimal number in lower or upper
 * @types: lsta of arguments
 * @map_to: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @flag_ch: Calculates active flags
 * @width: get width
 * @precsion: precsion specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int myprindx_hex(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precsion, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precsion, size));
}
