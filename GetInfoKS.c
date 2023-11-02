#include "shell.h"

/**
 * clear_info - Initializes info_t structure
 * @info: The structure containing potential arguments.
 */

void clear_info(info_t *info)
{
	info->input_string = NULL;
	info->input_array = NULL;
	info->current_path = NULL;
	info->argument_count = 0;
}

/**
 * set_info - Initializes info_t structure
 * @info: The structure containing potential arguments.
 * @agv: The argument vector
 */

void set_info(info_t *info, char **agv)
{
	int xs = 0;

	info->program_filename = agv[0];
	if (info->input_string)
	{
		info->input_array = string_to_words(info->input_string, " \t");
		if (!info->input_array)
		{
			info->input_array = malloc(sizeof(char *) * 2);
			if (info->input_array)
			{
				info->input_array[0] = str_dup(info->input_string);
				info->input_array[1] = NULL;
			}
		}
		for (xs = 0; info->input_array && info->input_array[xs]; xs++)
			;
		info->argument_count = xs;

		alias_rep(info);
		vars_rep(info);
	}
}

/**
 * free_info - Frees info_t structure fields
 * @info: The structure containing potential arguments.
 * @all: Returns true if freeing all fields
 */

void free_info(info_t *info, int all)
{
	str_free(info->input_array);
	info->input_array = NULL;
	info->current_path = NULL;
	if (all)
	{
		if (!info->command_buffer)
			free(info->input_string);
		if (info->env_variable)
			free_list(&(info->env_variable));
		if (info->history_list)
			free_list(&(info->history_list));
		if (info->alias_list)
			free_list(&(info->alias_list));
		str_free(info->modified_env_variable);
			info->modified_env_variable = NULL;
		pntr_free((void **)info->command_buffer);
		if (info->read_file_descriptor > 2)
			close(info->read_file_descriptor);
		_putchar(BUF_FLUSH);
	}
}
