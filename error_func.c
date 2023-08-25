#include "shell.h"

/**
 * puts_err - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void puts_err(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		putchar_err(str[i]);
		i++;
	}
}
/**
 * putchar_err - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On failure, -1 is returned
 */
int putchar_err(char c)
{
	static int i;
	static char buf[BUFFER_SIZE_WRITE];

	if (c == NEG_ONE || i >= BUFFER_SIZE_WRITE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != NEG_ONE)
		buf[i++] = c;
	return (1);
}
