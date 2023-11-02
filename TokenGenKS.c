#include "shell.h"

/**
 * **string_to_words2 - Splits string into words
 * @str: A string input
 * @dlmtr: A delimeter
 * Return: Returns array of strings pointer, NULL on failure
 */

char **string_to_words2(char *str, char dlmtr)
{
	int xk, jk, kk, mk, numwords = 0;
	char **st;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (xk = 0; str[xk] != '\0'; xk++)
		if ((str[xk] != dlmtr && str[xk + 1] == dlmtr) ||
				    (str[xk] != dlmtr && !str[xk + 1]) || str[xk + 1] == dlmtr)
			numwords++;
	if (numwords == 0)
		return (NULL);
	st = malloc((1 + numwords) * sizeof(char *));
	if (!st)
		return (NULL);
	for (xk = 0, jk = 0; jk < numwords; jk++)
	{
		while (str[xk] == dlmtr && str[xk] != dlmtr)
			xk++;
		kk = 0;
		while (str[xk + kk] != dlmtr && str[xk + kk] && str[xk + kk] != dlmtr)
			kk++;
		st[jk] = malloc((kk + 1) * sizeof(char));
		if (!st[jk])
		{
			for (kk = 0; kk < jk; kk++)
				free(st[kk]);
			free(st);
			return (NULL);
		}
		for (mk = 0; mk < kk; mk++)
			st[jk][mk] = str[xk++];
		st[jk][mk] = 0;
	}
	st[jk] = NULL;
	return (st);
}

/**
 * **string_to_words - Splits string into words. Repeat delimiters ignored
 * @str: A string input
 * @dlmtr: A string delimeter
 * Return: The pointer to an array of strings, or NULL on failure
 */

char **string_to_words(char *str, char *dlmtr)
{
	int xk, jk, kk, mk, numwords = 0;
	char **st;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!dlmtr)
		dlmtr = " ";
	for (xk = 0; str[xk] != '\0'; xk++)
		if (!is_delim(str[xk], dlmtr) &&
			(is_delim(str[xk + 1], dlmtr) || !str[xk + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	st = malloc((1 + numwords) * sizeof(char *));
	if (!st)
		return (NULL);
	for (xk = 0, jk = 0; jk < numwords; jk++)
	{
		while (is_delim(str[xk], dlmtr))
			xk++;
		kk = 0;
		while (!is_delim(str[xk + kk], dlmtr) && str[xk + kk])
			kk++;
		st[jk] = malloc((kk + 1) * sizeof(char));
		if (!st[jk])
		{
			for (kk = 0; kk < jk; kk++)
				free(st[kk]);
			free(st);
			return (NULL);
		}
		for (mk = 0; mk < kk; mk++)
			st[jk][mk] = str[xk++];
		st[jk][mk] = 0;
	}
	st[jk] = NULL;
	return (st);
}
