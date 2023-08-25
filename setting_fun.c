#include"shell.h"

/**
 * set_data - initializes info_s struct
 * @info: struct address
 * @av: argument vector
 */
void set_data(info_s *info, char **av)
{
	int i = 0;

	info->prog_name = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;
		change_alias(info);
		change_v(info);
	}
}

/**
 * link_at_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_s *link_at_end(list_s **head, const char *str, int num)
{
	list_s *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_s));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_s));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}


/**
 * display_vector - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: Array of strings.
 */

char **display_vector(list_s *head)
{
	list_s *node = head;
	size_t i = _listlen(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));

	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * make_empty_vector - frees memory allocated to a 2D character array
 * @vec: Vector to be freed.
 *
 * Return: Nothing.
 */

void make_empty_vector(char **vec)
{
	char **ptr = vec;

	if (!vec)
		return;
	while (*vec)
		free(*vec++);

	free(ptr);
}

/**
 * set_nulls - sets all the characters in a char array to nulls
 * @arr: Array to be initialized.
 * @size: Size of the array.
 *
 * Return: Nothing
 */

void set_nulls(char *arr, size_t size)
{
	size_t x;

	for (x = 0; x < size; x++)
		arr[x] = '\0';
}

