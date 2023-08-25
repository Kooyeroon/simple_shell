#include "shell.h"

/**
 * take_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */


ssize_t take_input(info_s *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(NEG_ONE);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		chain_checking(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->sep_buff_kind = REG_FLAG;
		}
		*buf_p = p;
		return (_strlen(p));
	}
	*buf_p = buf;
	return (r);
}


/**
 * duplic - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplic(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;

	return (buf);
}

/**
 * alias_set - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_set(info_s *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));
	unset_alias(info, str);
	return (link_at_end(&(info->alias), str, 0) == NULL);
}
