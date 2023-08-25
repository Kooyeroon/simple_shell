#include "shell.h"
/**
 * cd_fun - changes the current directory of the process
 * @info: contains simulated arguments for a function pointer,
 *		  allowing for a consistent function prototype
 *
 * Return: 0
 */

int cd_fun(info_s *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);

	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		puts_err(info->argv[1]), putchar_err('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _setenv - Adds or updates an environment variable.
 * @info: Structure containing the environment variables.
 *		  Used to maintain constant function prototype.
 * @var: The name of the environment variable to add or update.
 * @value: The value of the environment variable to add or update.
 * Return: 0 if the environment variable was succ
 * essfully added or updated, else 1.
 */

int _setenv(info_s *info, char *var, char *value)
{
	char *buf = NULL;
	list_s *node;
	char *p;

	if (!var || !value)
		return (1);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);

	node = info->env;

	while (node)
	{
		p = begin_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	link_at_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}


/**
 * setenv_checking - Checks if an environment variable has been set.
 * @info: contains simulated arguments for a function pointer,
 * allowing for a consistent function prototype
 *
 * Return: 0 if set, else 1.
 */

int setenv_checking(info_s *info)
{
	if (info->argc != 3)
	{
		puts_err("Incorrect number of arguements\n");
		return (1);
	}

	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string,
 * converted integer else -1
 */
void print_error(info_s *info, char *estr)
{
	puts_err(info->prog_name);
	puts_err(": ");
	display_dec(info->lines, STDERR_FILENO);
	puts_err(": ");
	puts_err(info->argv[0]);
	puts_err(": ");
	puts_err(estr);
}

/**
 * create_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int create_history(info_s *info)
{
	ssize_t fd;
	char *filename = read_hist(info);
	list_s *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		write_chars(node->str, fd);
		write_char('\n', fd);
	}
	write_char(NEG_ONE, fd);
	close(fd);
	return (1);
}


