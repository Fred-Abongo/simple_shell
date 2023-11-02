#include "shell.h"

/**
 * path_finder - Finds this cmd in PATH string
 * @info: The structure containing potential arguments.
 * @strpath: String PATH
 * @cmd: cmd to be found
 * Return: Returns full path of cmd if found or returns NULL
 */

char *path_finder(info_t *info, char *strpath, char *cmd)
{
	int xk = 0, curr_psn = 0;
	char *current_path;

	if (!strpath)
		return (NULL);
	if ((str_len(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_exe_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!strpath[xk] || strpath[xk] == ':')
		{
			current_path = dups_chars(strpath, curr_psn, xk);
			if (!*current_path)
				str_cat(current_path, cmd);
			else
			{
				str_cat(current_path, "/");
				str_cat(current_path, cmd);
			}
			if (is_exe_cmd(info, current_path))
				return (current_path);
			if (!strpath[xk])
				break;
			curr_psn = xk;
		}
		xk++;
	}
	return (NULL);
}

/**
 * is_exe_cmd - Determines whether a file is an executable command
 * @info: The structure containing potential arguments.
 * @path: The file path
 * Return: Returns 1 if true, return 0 otherwise
 */

int is_exe_cmd(info_t *info, char *path)
{
	struct stat stt;

	(void)info;
	if (!path || stat(path, &stt))
		return (0);

	if (stt.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dups_chars - Duplicates the characters
 * @strpath: A string PATH
 * @strt: A starting index
 * @stp: A stopping index
 * Return: Returns new buffer pointer
 */

char *dups_chars(char *strpath, int strt, int stp)
{
	static char buf[1024];
	int xk = 0, sk = 0;

	for (sk = 0, xk = strt; xk < stp; xk++)
		if (strpath[xk] != ':')
			buf[sk++] = strpath[xk];
	buf[sk] = 0;
	return (buf);
}
