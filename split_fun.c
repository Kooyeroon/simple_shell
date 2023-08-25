#include "shell.h"

/**
 * split_to_string - splits a string into words specified by a delimiter(s),
 *				  storing the pointer to each word (null-terminated)
 *				  in an array.
 * @str: String to be split.
 * @separators: One or more delimiters by which to split the string.
 * @word_count: Number of words in the string (separated by the delimiters).
 *
 * Return: Vector of pointers to strings (words).
 *		   Remember to free vector after use.
 */

char **split_to_string(char *str, char *separators, size_t *word_count)
{
	int v, no_of_words;
	char **words;
	char *str_ptr = str;
	unsigned int c, word_sizes[MAX_WORD_COUNT];

	set_zeros(word_sizes, MAX_WORD_COUNT);
	no_of_words = words_count(str, separators, word_sizes);

	if (no_of_words == 0)
		return (NULL);
	words = malloc((sizeof(char *) * no_of_words) + 1);
	if (!words)
		return (NULL);
	for (v = 0; v < no_of_words; v++)
	{
		words[v] = malloc((sizeof(char) * word_sizes[v]) + 1);
		if (!words[v])
		{
			for (v--; v >= 0; v--)
				free(words[v]);
			free(words);
			return (NULL);
		}
		for (c = 0; c < word_sizes[v]; c++, str_ptr++)
		{
			while (is_delimiter(*str_ptr, separators))
				str_ptr++;

			words[v][c] = *str_ptr;
		};

		words[v][c] = '\0';
	}
	*word_count = no_of_words;
	words[v] = NULL;

	return (words);
}

/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}


/**
**_strncpy - copies a string
*@dest: the destination string to be copied to
*@src: the source string
*@n: the amount of characters to be copied
*Return: the concatenated string
*/
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}


/**
 * terminal_prompt - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if from_terminal mode else 0
 */

int terminal_prompt(info_s *info)
{
	return (isatty(STDIN_FILENO) && info->fd_read <= 2);
}


