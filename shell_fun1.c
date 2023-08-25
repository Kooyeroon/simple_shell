#include "shell.h"
/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct as in shell.h
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter else 0
 */
bool is_chain(info_s *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->sep_buff_kind = OR_FLAG;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->sep_buff_kind = AND_FLAG;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->sep_buff_kind = CHAIN_FLAG;
	}
	else
		return (false);
	*p = j;
	return (true);
}
/**
 * shell_main - main control for the shell program
 * @info: pointer to an info_s struct containing shell information
 * @av: array of strings containing arguments to the shell
 *
 * Return: the status of the last executed builtin command
 */
int shell_main(info_s *info, char **av)
{
	ssize_t read_result = 0;
	int builtin_return_value = 0;

	while (read_result != -1 && builtin_return_value != -2)
	{
		clear_info(info);

		if (terminal_prompt(info))
			_puts("$ ");

		putchar_err(NEG_ONE);
		read_result = take_input(info);

		if (read_result != -1)
		{
			set_data(info, av);
			builtin_return_value = control_builtin(info);

			if (builtin_return_value == -1)
				check_command(info);
		}

		else if (terminal_prompt(info))
			_putchar('\n');

		free_info(info, 0);
	}

	create_history(info);

	free_info(info, 1);
	if (!terminal_prompt(info) && info->status)
		exit(info->status);

	if (builtin_return_value == -2)
	{
		if (info->error_code == -1)
			exit(info->status);
		exit(info->error_code);
	}
	return (builtin_return_value);
}
/**
 * is_executable - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
bool is_executable(info_s *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (true);
	}
	return (false);
}

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_s *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->sep_buff);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, handle_sigint);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->lc_flag = 1;
			handle_comments(*buf);
			upgrade_history(info, *buf, info->hist_lines++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->sep_buff = buf;
			}
		}
	}
	return (r);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_s *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
							   get_node_index(info->alias, node_str_start(info->alias, str, -1)));
	*p = c;
	return (ret);
}
