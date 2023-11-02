#include "shell.h"

/**
 * main - The main entry point
 * @ac: An argument count
 * @av: An argument vector
 * Return: Returns 0 if successful and 1 if an error
 */

int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				eput_str(av[0]);
				eput_str(": 0: Can't open ");
				eput_str(av[1]);
				eput_char('\n');
				eput_char(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->read_file_descriptor = fd;
	}
	pop_env_list(info);
	read_history(info);
	shell_loop(info, av);
	return (EXIT_SUCCESS);
}
