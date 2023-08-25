#include "shell.h"

/**
 * change_v - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int change_v(info_s *info)
{
	int i = 0;
	list_s *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;
		if (!_strcmp(info->argv[i], "$?"))
		{
			change_string(&(info->argv[i]),

						   _strdup(base_changing(info->status, 10, 0)));

			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			change_string(&(info->argv[i]),

						   _strdup(base_changing(getpid(), 10, 0)));

			continue;
		}
		node = node_str_start(info->env, &info->argv[i][1], '=');
		if (node)
		{
			change_string(&(info->argv[i]),

						   _strdup(_strchr(node->str, '=') + 1));

			continue;
		}
		change_string(&info->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * check_command - searches for a command in PATH or the current directory
 * @info: a pointer to the parameter and return info struct
 *
 * Return: void
 */
void check_command(info_s *info)
{
	char *path = NULL;
	int i, word_count;

	info->path = info->argv[0];
	if (info->lc_flag == 1)
	{
		info->lines++;
		info->lc_flag = 0;
	}

	/* Count the number of non-delimiter words in the argument */
	for (i = 0, word_count = 0; info->arg[i]; i++)
		if (!is_delimiter(info->arg[i], " \t\n"))
			word_count++;

	/* If there are no words, exit without doing anything */
	if (!word_count)
		return;

	/* Check if the command is in the PATH variable */
	path = check_file_in_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		create_process(info);
	}
	else
	{
		/* Check if the command is in the current directory */
		if ((terminal_prompt(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && is_executable(info, info->argv[0]))
			create_process(info);
		/* If the command is not found, print an error message */
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * check_file_in_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *check_file_in_path(info_s *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && begin_with(cmd, "./"))
	{
		if (is_executable(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = duplic(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_executable(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_s *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->fd_read, buf, BUFFER_SIZE_READ);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_s *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

