#include "shell.h"

/**
 * eput_str - Prints input string
 * @str: The printed string
 * Return: Returns nothing
 */

void eput_str(char *str)
{
	int xs = 0;

	if (!str)
		return;
	while (str[xs] != '\0')
	{
		eput_char(str[xs]);
		xs++;
	}
}

/**
 * eput_char - Writes character c to stderr
 * @ch: The character to print
 * Return: Returns 1 On success.
 * returns -1 on error, and errno is set appropriately.
 */

int eput_char(char ch)
{
	static int xs;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || xs >= WRITE_BUF_SIZE)
	{
		write(2, buf, xs);
		xs = 0;
	}
	if (ch != BUF_FLUSH)
		buf[xs++] = ch;
	return (1);
}

/**
 * _putfd - Writes character c to given fdr
 * @ch: The printed character
 * @fdr: The filedescriptor to write on
 * Return: Returns 1 on success.
 * returns -1 on error, and errno is set appropriately.
 */

int _putfd(char ch, int fdr)
{
	static int xs;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || xs >= WRITE_BUF_SIZE)
	{
		write(fdr, buf, xs);
		xs = 0;
	}
	if (ch != BUF_FLUSH)
		buf[xs++] = ch;
	return (1);
}

/**
 * _putsfd - Prints string input
 * @str: The printed string
 * @fdr: Filedescriptor to write on
 * Return: Returns the number of chars put
 */

int _putsfd(char *str, int fdr)
{
	int xs = 0;

	if (!str)
		return (0);
	while (*str)
	{
		xs += _putfd(*str++, fdr);
	}
	return (xs);
}
