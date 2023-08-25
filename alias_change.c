#include "shell.h"

/**
 * change_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int change_alias(info_s *info)
{
	int i;
	list_s *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_str_start(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}

	return (1);
}

/**
 * _printenv - prints the current environment
 * @info: contains simulated arguments for a function pointer,
 * allowing for a consistent function prototype
 * Return: Always 0
 */
int _printenv(info_s *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * handle_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: 0;
 */

void handle_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: contains simulated arguments for a function pointer,
 *
 * Return: the new hist_lines
 */
int renumber_history(info_s *info)
{
	list_s *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->hist_lines = i);
}




