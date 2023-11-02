#include "shell.h"

/**
 * _erratoi - Converts string to an integer
 * @st: The converted string
 * Return: Returns 0 if no numbers in string, converted number otherwise
 * returns -1 on error
 */

int _erratoi(char *st)
{
	int xs = 0;
	unsigned long int result = 0;

	if (*st == '+')
		st++;
	for (xs = 0;  st[xs] != '\0'; xs++)
	{
		if (st[xs] >= '0' && st[xs] <= '9')
		{
			result *= 10;
			result += (st[xs] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - Prints error message
 * @info: The structure containing potential arguments.
 * @err_str: A string containing specified error type
 * Return: Returns 0 if no numbers in string, converted number otherwise
 *        returns -1 on error
 */

void print_error(info_t *info, char *err_str)
{
	eput_str(info->program_filename);
	eput_str(": ");
	print_d(info->error_count, STDERR_FILENO);
	eput_str(": ");
	eput_str(info->input_array[0]);
	eput_str(": ");
	eput_str(err_str);
}

/**
 * print_d - Function to print decimal (integer) number (base 10)
 * @input: The input
 * @fdr: Filedescriptor to write on
 * Return: Returns number of printed characters
 */

int print_d(int input, int fdr)
{
	int (*__putchar)(char) = _putchar;
	int xs, count = 0;
	unsigned int _abs_, current;

	if (fdr == STDERR_FILENO)
		__putchar = eput_char;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (xs = 1000000000; xs > 1; xs /= 10)
	{
		if (_abs_ / xs)
		{
			__putchar('0' + current / xs);
			count++;
		}
		current %= xs;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_num - Function converter, str-numb clone
 * @numb: The number
 * @base: The base
 * @flags: Flags argument
 * Return: Returns string
 */

char *convert_num(long int numb, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long ns = numb;

	if (!(flags & CONVERT_UNSIGNED) && numb < 0)
	{
		ns = -numb;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[ns % base];
		ns /= base;
	} while (ns != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - Replaces first instance of '#' with '\0'
 * @buf: String modified address
 * Return: Returns 0 always;
 */

void remove_comments(char *buf)
{
	int xs;

	for (xs = 0; buf[xs] != '\0'; xs++)
		if (buf[xs] == '#' && (!xs || buf[xs - 1] == ' '))
		{
			buf[xs] = '\0';
			break;
		}
}
