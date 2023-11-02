#include "shell.h"

/**
 * str_cpy - Copies a string
 * @bdestn: Buffer destination
 * @src: Source
 * Return: Returns destination pointer
 */

char *str_cpy(char *bdestn, char *src)
{
	int xk = 0;

	if (bdestn == src || src == 0)
		return (bdestn);
	while (src[xk])
	{
		bdestn[xk] = src[xk];
		xk++;
	}
	bdestn[xk] = 0;
	return (bdestn);
}

/**
 * str_dup - Stirng duplicator
 * @str: String duplicated
 * Return: Returns duplicated string pointer
 */

char *str_dup(const char *str)
{
	int length = 0;
	char *retn;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	retn = malloc(sizeof(char) * (length + 1));
	if (!retn)
		return (NULL);
	for (length++; length--;)
		retn[length] = *--str;
	return (retn);
}

/**
 * _puts - Prints string input
 * @str: String printed
 * Return: Returns nothing
 */

void _puts(char *str)
{
	int xk = 0;

	if (!str)
		return;
	while (str[xk] != '\0')
	{
		_putchar(str[xk]);
		xk++;
	}
}

/**
 * _putchar - Writes character c to stdout
 * @ch: Character printed
 * Return: Returns 1 on success.
 * On error, -1 is returned, & errno set appropriately.
 */

int _putchar(char ch)
{
	static int xk;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || xk >= WRITE_BUF_SIZE)
	{
		write(1, buf, xk);
		xk = 0;
	}
	if (ch != BUF_FLUSH)
		buf[xk++] = ch;
	return (1);
}
