#include "shell.h"
/**
 * clear_info - initializes info_s struct
 * @info: struct address
 */
void clear_info(info_s *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * add_node_start - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_s *add_node_start(list_s **head, const char *str, int num)
{
	list_s *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_s));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_s));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * _listlen - gets the length of linked list
 * @h: Pointer to first node.
 *
 * Return: Size of list.
 */
size_t _listlen(const list_s *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * _memset - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 * Return: s- a pointer to the memory area of s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * set_zeros - sets all the bytes of an integer array to 0
 * @arr: Array to be initialized.
 * @size: Size of the array.
 *
 * Return: Nothing
 */

void set_zeros(unsigned int *arr, size_t size)
{
	size_t x;

	for (x = 0; x < size; x++)
		arr[x] = 0;
}

