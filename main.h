#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmt - Struct op
 *
 * @fmt: The format.
 * @fn: The function associated.
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct fmt fmt_t - Struct op
 *
 * @fmt: The format.
 * @fm_t: The function associated.
 */
typedef struct fmt fmt_t;

int _printf(const char *formt, ...);
int format_handler(const char *fmt, int *i,
va_list lst, char buffer[], int flags, int width, int precsion, int size);

/****************** FUNCTIONS ******************/

/* Funtions to print chars and strings */
int miprint_char(va_list types, char buffer[],
	int flags, int width, int precsion, int size);
int miprint_string(va_list types, char buffer[],
	int flags, int width, int precsion, int size);
int miprint_percent(va_list types, char buffer[],
	int flags, int width, int precsion, int size);

/* Fctns to print numbers */
int miprint_int(va_list types, char buffer[],
	int flags, int width, int precsion, int size);
int miprint_binary(va_list types, char buffer[],
	int flags, int width, int precsion, int size);
int myprindx_unsigned(va_list types, char buffer[],
	int flags, int width, int precsion, int size);
int myprindx_octa(va_list types, char buffer[],
	int flags, int width, int precsion, int size);
int myprindx_hexdeci(va_list types, char buffer[],
	int flags, int width, int precsion, int size);
int myprindx_hex_upp(va_list types, char buffer[],
	int flags, int width, int precsion, int size);

int myprindx_hex(va_list types, char map_to[],
char buffer[], int flags, char flag_ch, int width, int precsion, int size);

/* Fctn to print non printable characters */
int myprindx_non_print(va_list types, char buffer[],
	int flags, int width, int precsion, int size);

/* Fctns to print memory address */
int myprindx_point(va_list types, char buffer[],
	int flags, int width, int precsion, int size);

/* Fctn to handle other specifiers */
int gt_flgs(const char *formt, int *i);
int gt_wdth(const char *formt, int *i, va_list lst);
int get_exact(const char *formt, int *i, va_list lst);
int gt_siz(const char *formt, int *i);

/*Fctn to print string in reverse*/
int myprindx_rev(va_list types, char buffer[],
	int flags, int width, int precsion, int size);

/*Fctn to print a string in rot 13*/
int myprindx_rot13string(va_list types, char buffer[],
	int flags, int width, int precsion, int size);

/* width handler */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precsion, int size);
int writ_num(int is_positive, int indx, char buffer[],
	int flags, int width, int precsion, int size);
int write_num(int indx, char bff[], int flags, int width, int precsion,
	int length, char padd, char extra_c);
int write_pointer(char buffer[], int indx, int length,
	int width, int flags, char padd, char extra_c, int padd_start);

int write_unsgnd(int iz_negtive, int indx,
char buffer[],
	int flags, int width, int precsion, int size);

/****************** UTILS ******************/
int iz_printable(char);
int append_hexa_code(char, char[], int);
int iz_digit(char);

long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);

#endif /* MAIN_H */
