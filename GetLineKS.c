#include "shell.h"

/**
 * input_buf - Buffers chained commands
 * @info: The structure containing potential arguments.
 * @buf: The buffer address
 * @len: The len var address
 * Return: Returns bytes read
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t rs = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		rs = getline(buf, &len_p, stdin);
#else
		rs = _getline(info, buf, &len_p);
#endif
		if (rs > 0)
		{
			if ((*buf)[rs - 1] == '\n')
			{
				(*buf)[rs - 1] = '\0';
				rs--;
			}
			info->count_current_line = 1;
			remove_comments(*buf);
			build_hist_list(info, *buf, info->hist_line_count++);
			{
				*len = rs;
				info->command_buffer = buf;
			}
		}
	}
	return (rs);
}

/**
 * get_input - Gets a line minus the newline
 * @info: The structure containing potential arguments.
 * Return: Returns bytes read
 */

ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t xs, js, len;
	ssize_t rs = 0;
	char **buf_p = &(info->input_string), *ps;

	_putchar(BUF_FLUSH);
	rs = input_buf(info, &buf, &len);
	if (rs == -1)
		return (-1);
	if (len)
	{
		js = xs;
		ps = buf + xs;

		check_chain(info, buf, &js, xs, len);
		while (js < len)
		{
			if (is_chain(info, buf, &js))
				break;
			js++;
		}

		xs = js + 1;
		if (xs >= len)
		{
			xs = len = 0;
			info->command_buffer_type = CMD_NORM;
		}

		*buf_p = ps;
		return (str_len(ps));
	}

	*buf_p = buf;
	return (rs);
}

/**
 * read_buf - Reads a buffer
 * @info: The structure containing potential arguments.
 * @buf: The buffer
 * @x: The size
 * Return: Returns rs
 */

ssize_t read_buf(info_t *info, char *buf, size_t *x)
{
	ssize_t rs = 0;

	if (*x)
		return (0);
	rs = read(info->read_file_descriptor, buf, READ_BUF_SIZE);
	if (rs >= 0)
		*x = rs;
	return (rs);
}

/**
 * _getline - Gets next line of input from STDIN
 * @info: The structure containing potential arguments.
 * @ptr: Buffer address pointed to, preallocated or NULL
 * @length: Size of preallocated ptr buffer if not NULL
 * Return: Returns ss
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t is, len;
	size_t xs;
	ssize_t rs = 0, ss = 0;
	char *qs = NULL, *new_p = NULL, *cs;

	qs = *ptr;
	if (qs && length)
		ss = *length;
	if (is == len)
		is = len = 0;

	rs = read_buf(info, buf, &len);
	if (rs == -1 || (rs == 0 && len == 0))
		return (-1);

	cs = str_chr(buf + is, '\n');
	xs = cs ? 1 + (unsigned int)(cs - buf) : len;
	new_p = mem_realloc(qs, ss, ss ? ss + xs : xs + 1);
	if (!new_p)
		return (qs ? free(qs), -1 : -1);

	if (ss)
		str_n_cat(new_p, buf + is, xs - is);
	else
		str_n_cpy(new_p, buf + is, xs - is + 1);

	ss += xs - is;
	is = xs;
	qs = new_p;

	if (length)
		*length = ss;
	*ptr = qs;
	return (ss);
}

/**
 * sigintHandler - Blocks ctrl-C
 * @sig_numb: The signal number
 * Return: Returns void
 */

void sigintHandler(__attribute__((unused))int sig_numb)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
