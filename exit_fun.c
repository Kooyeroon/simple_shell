#include "shell.h"

/**
 * exit_fun - exits the shell
 * @info: contains simulated arguments for a func pointer,
 * allowing for a consistent function prototype
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */

int exit_fun(info_s *info)
{
	int exitcheck;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		exitcheck = err_num(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			puts_err(info->argv[1]);
			putchar_err('\n');
			return (1);
		}
		info->error_code = err_num(info->argv[1]);
		return (-2);
	}
	info->error_code = -1;
	return (-2);
}

/**
 * get_environ - Returns a copy of the environment variables as an array of strings.
 * @info: Structure containing the environment variables.
 *		  Used to maintain constant function prototype.
 * Return: The environment variables as an array of strings.
 */

char **get_environ(info_s *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = display_vector(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}


/**
 * _getenv - gets the value of an environ variable
 * @info: contains simulated arguments for a function pointer,
 * @name: env var name
 *
 * Return: the value
 */

char *_getenv(info_s *info, const char *name)
{
	char *p;
	list_s *node = info->env;

	while (node)
	{
		p = begin_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}


/**
 * err_num - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string,
 * converted integer else -1
 *
 */
int err_num(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}


/**
 * read_hist - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *read_hist(info_s *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE_NAME) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE_NAME);
	return (buf);
}

