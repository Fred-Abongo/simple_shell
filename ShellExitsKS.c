#include "shell.h"

/**
 * *str_n_cpy - Copies a string
 * @dest: String destination to copy to
 * @src: String source
 * @mk: Amount of copied characters
 * Return: Returns the concatenated string
 */

char *str_n_cpy(char *dest, char *src, int mk)
{
	int xk, jk;
	char *st = dest;

	xk = 0;
	while (src[xk] != '\0' && xk < mk - 1)
	{
		dest[xk] = src[xk];
		xk++;
	}
	if (xk < mk)
	{
		jk = xk;
		while (jk < mk)
		{
			dest[jk] = '\0';
			jk++;
		}
	}
	return (st);
}

/**
 * *str_n_cat - Concatenates two strings
 * @dest: First string
 * @src: A second string
 * @mk: Maximum amount of bytes to be used
 * Return: Returns the concatenated string
 */

char *str_n_cat(char *dest, char *src, int mk)
{
	int xk, jk;
	char *st = dest;

	xk = 0;
	jk = 0;
	while (dest[xk] != '\0')
		xk++;
	while (src[jk] != '\0' && jk < mk)
	{
		dest[xk] = src[jk];
		xk++;
		jk++;
	}
	if (jk < mk)
		dest[xk] = '\0';
	return (st);
}

/**
 * *str_chr - Locates character in a string
 * @st: Parsed string
 * @chk: Looked for character
 * Return: (st) a pointer to the memory area st
 */

char *str_chr(char *st, char chk)
{
	do {
		if (*st == chk)
			return (st);
	} while (*st++ != '\0');

	return (NULL);
}
