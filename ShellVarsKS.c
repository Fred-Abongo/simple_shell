#include "shell.h"

/**
 * is_chain - Test if current buffer char is a chain delimeter
 * @info: The structure containing potential arguments.
 * @buf: Buffer char
 * @pstn: Current position address in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */

int is_chain(info_t *info, char *buf, size_t *pstn)
{
	size_t pk = *pstn;

	if (buf[pk] == '|' && buf[pk + 1] == '|')
	{
		buf[pk] = 0;
		pk++;
		info->command_buffer_type = CMD_OR;
	}
	else if (buf[pk] == '&' && buf[pk + 1] == '&')
	{
		buf[pk] = 0;
		pk++;
		info->command_buffer_type = CMD_AND;
	}
	else if (buf[pk] == ';')
	{
		buf[pk] = 0;
		info->command_buffer_type = CMD_CHAIN;
	}
	else
		return (0);
	*pstn = pk;
	return (1);
}

/**
 * check_chain - The checks to continue chaining based on last status
 * @info: The structure containing potential arguments.
 * @buf: Character buffer
 * @pstn: Current position address in buf
 * @idx: Starting position in buf
 * @len: Buf length
 * Return: Returns Void
 */

void check_chain(info_t *info, char *buf, size_t *pstn, size_t idx, size_t len)
{
	size_t xk = *pstn;

	if (info->command_buffer_type == CMD_AND)
	{
		if (info->command_status)
		{
			buf[idx] = 0;
			xk = len;
		}
	}
	if (info->command_buffer_type == CMD_OR)
	{
		if (!info->command_status)
		{
			buf[idx] = 0;
			xk = len;
		}
	}

	*pstn = xk;
}

/**
 * alias_rep - Replaces aliases in the tokenized string
 * @info: The structure containing potential arguments.
 * Return: Returns 1 if replaced, 0 otherwise
 */

int alias_rep(info_t *info)
{
	int xk;
	list_t *node;
	char *sk;

	for (xk = 0; xk < 10; xk++)
	{
		node = node_startswith(info->alias_list, info->input_array[0], '=');
		if (!node)
			return (0);
		free(info->input_array[0]);
		sk = str_chr(node->str, '=');
		if (!sk)
			return (0);
		sk = str_dup(sk + 1);
		if (!sk)
			return (0);
		info->input_array[0] = sk;
	}
	return (1);
}

/**
 * vars_rep - Replaces vars in the tokenized string
 * @info: The structure containing potential arguments.
 * Return: Returns 1 if replaced, 0 otherwise
 */

int vars_rep(info_t *info)
{
	int xk = 0;
	list_t *node;

	for (xk = 0; info->input_array[xk]; xk++)
	{
		if (info->input_array[xk][0] != '$' || !info->input_array[xk][1])
			continue;

		if (!str_cmp(info->input_array[xk], "$?"))
		{
			str_rep(&(info->input_array[xk]),
					str_dup(convert_num(info->command_status, 10, 0)));
			continue;
		}
		if (!str_cmp(info->input_array[xk], "$$"))
		{
			str_rep(&(info->input_array[xk]),
					str_dup(convert_num(getpid(), 10, 0)));
			continue;
		}
		node = node_startswith(info->env_variable, &info->input_array[xk][1], '=');
		if (node)
		{
			str_rep(&(info->input_array[xk]),
					str_dup(str_chr(node->str, '=') + 1));
			continue;
		}
		str_rep(&info->input_array[xk], str_dup(""));

	}
	return (0);
}

/**
 * str_rep - Replaces string
 * @ols: An old string address
 * @nws: A new string
 * Return: Returns 1 if replaced, 0 otherwise
 */

int str_rep(char **ols, char *nws)
{
	free(*ols);
	*ols = nws;
	return (1);
}
