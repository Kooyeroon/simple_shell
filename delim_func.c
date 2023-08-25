#include "shell.h"

/**
 * is_delimiter - checks if a character is a delimiter
 * @c: Character to be checked.
 * @delimiters: String of charaters to be compated.
 *
 * This function compares a character to one or more of delimiters
 * to see if the character matches any of the delimiters.
 *
 * Return: True if it is a delimiter, else false.
 */

bool is_delimiter(char c, char *delimiters)
{
	int s;

	for (s = 0; delimiters[s]; s++)
		if (c == delimiters[s])
			return (true);
	return (false);
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[BUFFER_SIZE_WRITE];

	if (c == NEG_ONE || i >= BUFFER_SIZE_WRITE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != NEG_ONE)
		buf[i++] = c;
	return (1);
}


/**
 * write_char - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On failure, -1 is returned
 */
int write_char(char c, int fd)
{
	static int i;
	static char buf[BUFFER_SIZE_WRITE];

	if (c == NEG_ONE || i >= BUFFER_SIZE_WRITE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != NEG_ONE)
		buf[i++] = c;
	return (1);
}
/**
 * write_chars - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int write_chars(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += write_char(*str++, fd);
	}
	return (i);
}

/**
 * words_count - counts the number of words in a string specified by
 *				 one or more delimiter. It also counts the length of
 *				 each word and stores them in an array.
 * @str: String to be parsed.
 * @separators: One or more delimiters to separate the string by.
 * @arr: Pointer to array where the word lengths will be stored.
 * Return: Number of words.
 */

int words_count(char *str, char *separators, unsigned int *arr)
{
	unsigned int c, d, word_len = 1, word_count = 0;
	char *str_copy = str;
	bool start = false, delimiter;

	if (!str)
		return (0);
	while (!start)
		for (d = 0; separators[d]; d++)
		{
			if (*str_copy == separators[d])
				str_copy++;
			else
				start = true;
		}
	if (!*(str_copy + 1))
	{
		arr[0] = 1;
		return (1);
	}
	for (c = 1; str_copy[c]; c++)
	{
		delimiter = is_delimiter(str_copy[c], separators);
		if (delimiter && !(is_delimiter(str_copy[c - 1], separators)))
		{
			arr[word_count] = word_len;
			word_count++;
		}
		if ((!str_copy[c + 1]) && !delimiter)
		{
			word_len++;
			arr[word_count] = word_len;
			word_count++;
			break;
		}
		if (!delimiter)
			word_len++;
		else
			word_len = 0;
	}
	return (word_count);
}


