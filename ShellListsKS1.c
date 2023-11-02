#include "shell.h"

/**
 * printed_list - Prints all the elements of list_t linked list
 * @hk: First node pointer
 * Return: Returns size of list
 */

size_t printed_list(const list_t *hk)
{
	size_t sk = 0;

	while (hk)
	{
		_puts(convert_num(hk->numb, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hk->str ? hk->str : "(nil)");
		_puts("\n");
		hk = hk->next;
		sk++;
	}
	return (sk);
}

/**
 * list_length - Determines linked list length
 * @xk: First node pointer
 * Return: Returns size of list
 */

size_t list_length(const list_t *xk)
{
	size_t nk = 0;

	while (xk)
	{
		xk = xk->next;
		nk++;
	}
	return (nk);
}

/**
 * node_index - Gets the node index
 * @fhd: List head pointer
 * @node: The node pointer
 * Return: Returns index of node or -1 if unsuccessful
 */

ssize_t node_index(list_t *fhd, list_t *node)
{
	size_t xk = 0;

	while (fhd)
	{
		if (fhd == node)
			return (xk);
		fhd = fhd->next;
		xk++;
	}
	return (-1);
}

/**
 * list_strings - Returns string array of the list->str
 * @fhd: First node pointer
 * Return: Returns the array of strings
 */

char **list_strings(list_t *fhd)
{
	list_t *node = fhd;
	size_t xk = list_length(fhd), jk;
	char **strs;
	char *str;

	if (!fhd || !xk)
		return (NULL);
	strs = malloc(sizeof(char *) * (xk + 1));
	if (!strs)
		return (NULL);
	for (xk = 0; node; node = node->next, xk++)
	{
		str = malloc(str_len(node->str) + 1);
		if (!str)
		{
			for (jk = 0; jk < xk; jk++)
				free(strs[jk]);
			free(strs);
			return (NULL);
		}

		str = str_cpy(str, node->str);
		strs[xk] = str;
	}
	strs[xk] = NULL;
	return (strs);
}

/**
 * node_startswith - Returns node with string starting with prefix
 * @node: List head pointer
 * @prefix: The string to match
 * @chr: Next character after prefix to match
 * Return: Returns match node or null
 */

list_t *node_startswith(list_t *node, char *prefix, char chr)
{
	char *qk = NULL;

	while (node)
	{
		qk = starts_with(node->str, prefix);
		if (qk && ((chr == -1) || (*qk == chr)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
