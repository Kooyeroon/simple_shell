#include "shell.h"


/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @q: the input string
 * @e: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *q, char *e)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (q == NULL || q[0] == 0)
		return (NULL);
	if (!e)
		e = " ";
	for (i = 0; q[i] != '\0'; i++)
		if (!is_delimiter(q[i], e) && (is_delimiter(q[i + 1], e) || !q[i + 1]))
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delimiter(q[i], e))
			i++;
		k = 0;
		while (!is_delimiter(q[i + k], e) && q[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			s[j][m] = q[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
**_strncat - concatenates two strings
*@dest: the first string
*@src: the second string
*@n: the amount of bytes to be maximally used
*Return: the concatenated string
*/
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}


/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}


/**
 * _isalpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic else 0 if not
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}


