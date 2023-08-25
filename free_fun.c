#include "shell.h"

/**
 * free_info - frees info_s struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_s *info, int all)
{
	make_empty_vector(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->sep_buff)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		make_empty_vector(info->environ);
		info->environ = NULL;
		bfree((void **)info->sep_buff);
		if (info->fd_read > 2)
			close(info->fd_read);
		_putchar(NEG_ONE);
	}
}

/**
 * print_list_str - prints only the str element of a list_s linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_s *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * print_list - prints all elements of a list_s linked list
 * @h: pointer to first node
 *
 * Return: Size of list
 */

size_t print_list(const list_s *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(base_changing(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}


/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous memory allocated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer of old block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
	p = malloc(new_size);
	if (!p)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}



