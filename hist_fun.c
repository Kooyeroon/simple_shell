#include "shell.h"

/**
 * control_history - displays the history list, one command by line, preceded
 *					with line numbers, starting at 0.
 * @info: contains simulated arguments for a function pointer,
 *		  constant function prototype.
 *	Return: Always 0
 */

int control_history(info_s *info)
{
	print_list(info->history);

	return (0);
}

/**
 * collect_env - populates env linked list
 * @info: contains simulated arguments for a function pointer,
 * allowing for a consistent function prototype
 * Return: Always 0
 */
int collect_env(info_s *info)
{
	list_s *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		link_at_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}


/**
 * base_changing - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *base_changing(long int num, int base, int flags)
{
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	static char *array;
	static char buffer[50];

	if (!(flags & BAS_CHANGE_UNSIG) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & BAS_CHANGE_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}


/**
 * upgrade_history - adds entry to a history linked list
 * @info: contains simulated arguments for a function pointer,
 * @buf: buffer
 * @linecount: the history linecount, hist_lines
 *
 * Return: Always 0
 */
int upgrade_history(info_s *info, char *buf, int linecount)
{
	list_s *node = NULL;

	if (info->history)
		node = info->history;
	link_at_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}


