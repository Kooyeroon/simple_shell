#include "shell.h"

/**
 * begin_with - checks if needle starts with haystack
 * @hs: string to search
 * @ne: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *begin_with(const char *hs, const char *ne)
{
	while (*ne)
		if (*ne++ != *hs++)
			return (NULL);
	return ((char *)hs);
}
/**
**_strchr - locates a character in a string
*@h: the string to be parsed
*@p: the character to look for
*Return: (s) a pointer to the memory area s
*/
char *_strchr(char *h, char p)
{
	do {
		if (*h == p)
			return (h);
	} while (*h++ != '\0');

	return (NULL);
}

/**
 * _puts - prints an input string
 * @s: the string to be printed
 *
 * Return: Nothing
 */

void _puts(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		_putchar(s[i]);
		i++;
	}
}

/**
 * _atoi - converts a string to an integer
 * @c: the string to be converted
 * Return: 0 if no numbers in string else converted integer
 */

int _atoi(char *c)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; c[i] != '\0' && flag != 2; i++)
	{
		if (c[i] == '-')
			sign *= -1;
		if (c[i] >= '0' && c[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (c[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}

/**
 * _strcat - concatenates two strings
 * @d: the destination buffer
 * @s: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *d, char *s)
{
	char *ret = d;

	while (*d)
		d++;
	while (*s)
		*d++ = *s++;
	*d = *s;
	return (ret);
}


