#include "shell.h"

/**
 * chain_checking - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void chain_checking(info_s *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->sep_buff_kind == AND_FLAG)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->sep_buff_kind == OR_FLAG)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	*p = j;
}

/**
 * control_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int control_builtin(info_s *info)
{
	int i, builtin_return_value = -1;

	builtin_commands builtints[] = {
		{"cd", cd_fun},
		{"env", _printenv},
		{"exit", exit_fun},
		{"help", help_fun},
		{"alias", alias_fun},
		{"setenv", setenv_checking},
		{"history", control_history},
		{"unsetenv", unsetenv_checking},
		{NULL, NULL}};

	for (i = 0; builtints[i].type; i++)
		if (_strcmp(info->argv[0], builtints[i].type) == 0)
		{
			info->lines++;
			builtin_return_value = builtints[i].func(info);
			break;
		}
	return (builtin_return_value);
}

