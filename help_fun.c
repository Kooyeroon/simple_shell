#include "shell.h"

/**
 * help_fun - prints a message for aa function not implemented
 * @info:	contains simulated arguments for a function pointer,
 *			constant function prototype.
 * Return: 0
 */

int help_fun(info_s *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);

	return (0);
}


/**
 * _unsetenv - Removes an environment variable.
 * @info: Structure containing the environment variables.
 *		  Used to maintain constant function prototype.
 * @var: The name of the environment variable to remove.
 * Return: 1 if the environment variable was successfully removed, else 0.
 */
int _unsetenv(info_s *info, char *var)
{
	list_s *node = info->env;
	size_t index = 0;
	char *p;

	if (!node || !var)
		return (0);
	while (node)
	{
		p = begin_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		index++;
	}

	return (info->env_changed);
}

/**
 * unsetenv_checking - Remove an environment variable
 * @info: contains simulated arguments for a function pointer,
 * allowing for a consistent function prototype
 * Return: Always 0
 */
int unsetenv_checking(info_s *info)
{
	int i;

	if (info->argc == 1)
	{
		puts_err("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}


/**
 * display_dec - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int display_dec(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = putchar_err;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{

		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;
	return (count);
}

/**
 * hist_read - reads history from file
 * @info: the parameter struct
 *
 * Return: hist_lines on success, 0 otherwise
 */
int hist_read(info_s *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = read_hist(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			upgrade_history(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		upgrade_history(info, buf + last, linecount++);
	free(buf);
	info->hist_lines = linecount;
	while (info->hist_lines-- >= HIST_SIZE_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->hist_lines);
}

