#include "shell.h"

/**
 * shell_loop - Shell main loop
 * @info: The structure containing potential arguments.
 * @varg: Vector arguments from main()
 * Return: Returns 0 on success, and 1 on error(error code)
 */

int shell_loop(info_t *info, char **varg)
{
	ssize_t sk = 0;
	int builtin_retn = 0;

	while (sk != -1 && builtin_retn != -2)
	{
		clear_info(info);
		if (is_interactive(info))
			_puts("$ ");
		eput_char(BUF_FLUSH);
		sk = get_input(info);
		if (sk != -1)
		{
			set_info(info, varg);
			builtin_retn = find_builtin(info);
			if (builtin_retn == -1)
				cmd_find(info);
		}
		else if (is_interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!is_interactive(info) && info->command_status)
		exit(info->command_status);
	if (builtin_retn == -2)
	{
		if (info->err_code == -1)
			exit(info->command_status);
		exit(info->err_code);
	}
	return (builtin_retn);
}
/**
 * cmd_fork - Forks an exec thread to run command
 * @info: The structure containing potential arguments.
 * Return: Returns void
 */

void cmd_fork(info_t *info)
{
	pid_t child_pd;

	child_pd = fork();
	if (child_pd == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pd == 0)
	{
		if (execve(info->current_path, info->input_array, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->command_status));
		if (WIFEXITED(info->command_status))
		{
			info->command_status = WEXITSTATUS(info->command_status);
			if (info->command_status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

/**
 * find_builtin - Builtin command finder
 * @info: The structure containing potential arguments.
 * Return: Returns -1 if builtin not found,
 * returns 0 if builtin executed successfully,
 * returns 1 if builtin found but not successful,
 * returns 2 if builtin signals exit()
 */

int find_builtin(info_t *info)
{
	int xk, built_in_retn = -1;
	builtin_table builtintbl[] = {
		{"exit", shl_exit},
		{"env", my_env},
		{"help", _cpd},
		{"history", hist_list},
		{"setenv", my_set_env},
		{"unsetenv", my_unset_env},
		{"cd", _cwd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (xk = 0; builtintbl[xk].type; xk++)
		if (str_cmp(info->input_array[0], builtintbl[xk].type) == 0)
		{
			info->error_count++;
			built_in_retn = builtintbl[xk].func(info);
			break;
		}
	return (built_in_retn);
}

/**
 * cmd_find - Finds command in PATH
 * @info: The structure containing potential arguments.
 * Return: Returns void
 */

void cmd_find(info_t *info)
{
	char *current_path = NULL;
	int sk, tk;

	info->current_path = info->input_array[0];
	if (info->count_current_line == 1)
	{
		info->error_count++;
		info->count_current_line = 0;
	}
	for (sk = 0, tk = 0; info->input_string[sk]; sk++)
		if (!is_delim(info->input_string[sk], " \t\n"))
			tk++;
	if (!tk)
		return;

	current_path = path_finder(info, get_env(info, "PATH="),
		info->input_array[0]);
	if (current_path)
	{
		info->current_path = current_path;
		cmd_fork(info);
	}
	else
	{
		if ((is_interactive(info) || get_env(info, "PATH=")
					|| info->input_array[0][0] == '/')
			&& is_exe_cmd(info, info->input_array[0]))
			cmd_fork(info);
		else if (*(info->input_string) != '\n')
		{
			info->command_status = 127;
			print_error(info, "not found\n");
		}
	}
}
