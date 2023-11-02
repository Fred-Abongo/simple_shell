#include "shell.h"

/**
 * hist_list - Displays history list, a command per line, preceded
 *              with line numbers, starting at 0.
 * @info: The structure containing potential arguments.
 * Return: Returns 0 always
 */

int hist_list(info_t *info)
{
	printed_list(info->history_list);
	return (0);
}

/**
 * unset_alias - Sets alias to string
 * @info: The structure containing potential arguments.
 * @str: The string alias
 * Return: Returns 0 on success, 1 on error
 */

int unset_alias(info_t *info, char *str)
{
	char *qs, cs;
	int retn;

	qs = str_chr(str, '=');
	if (!qs)
		return (1);
	cs = *qs;
	*qs = 0;
	retn = delete_node_at_index(&(info->alias_list),
		node_index(info->alias_list, node_startswith(info->alias_list, str, -1)));
	*qs = cs;
	return (retn);
}

/**
 * set_alias - Sets alias to string
 * @info: The structure containing potential arguments.
 * @str: The string alias
 * Return: Returns 0 on success, 1 on error
 */

int set_alias(info_t *info, char *str)
{
	char *qs;

	qs = str_chr(str, '=');
	if (!qs)
		return (1);
	if (!*++qs)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias_list), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string
 * @node: The alias node
 * Return: Returns 0 on success, 1 on error
 */

int print_alias(list_t *node)
{
	char *qs = NULL, *as = NULL;

	if (node)
	{
		qs = str_chr(node->str, '=');
		for (as = node->str; as <= qs; as++)
		_putchar(*as);
		_putchar('\'');
		_puts(qs + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Mimics the alias builtin (man alias)
 * @info: The structure containing potential arguments.
 * Return: Returns 0 always
 */

int _myalias(info_t *info)
{
	int xs = 0;
	char *qs = NULL;
	list_t *node = NULL;

	if (info->argument_count == 1)
	{
		node = info->alias_list;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (xs = 1; info->input_array[xs]; xs++)
	{
		qs = str_chr(info->input_array[xs], '=');
		if (qs)
			set_alias(info, info->input_array[xs]);
		else
			print_alias(node_startswith(info->alias_list, info->input_array[xs], '='));
	}

	return (0);
}
