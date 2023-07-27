#include "main.h"


/**
 * cmp_chars - determines if all characters in the input string
 * match any characters in the delimiter string
 * @string: input string parameter
 * @delim: delimiter string
 *
 * Return: true if all characters match or false otherwise.
 */
int cmp_chars(char string[], const char *delim)
{
	int isMatch;
	int i, j;

	for (i = 0; string[i]; i++)
	{
		isMatch = 0;

		for (j = 0; delim[j]; j++)
		{
			if (string[i] == delim[j])
			{
				isMatch = 1;
				break;
			}
		}
		if (!isMatch)
			return (0);
	}
	return (1);
}




/**
 * _strtok - splits string into tokens based on a set of delimiter characters
 * @string: input string.
 * @delim: delimiter.
 *
 * Return: tokenized string.
 */
char *_strtok(char string[], const char *delim)
{
	static char *token;
	unsigned int count, delim_checker;
	char *start_of_str;
	static char *end_of_str;


	if (string != NULL)
	{
		if (cmp_chars(string, delim))
			return (NULL);
		token = string;
		count = _strlen(string);
		end_of_str = &string[count];
	}
	start_of_str = token;
	if (start_of_str == end_of_str)
		return (NULL);
	for (delim_checker = 0; *token; token++)
	{
		if (token != start_of_str)
			if (*token && *(token - 1) == '\0')
				break;
		for (count = 0; delim[count]; count++)
		{
			if (*token == delim[count])
			{
				*token = '\0';
				if (token == start_of_str)
					start_of_str++;
				break;
			}
		}
		if (delim_checker == 0 && *token)
			delim_checker = 1;
	}
	if (delim_checker == 0)
		return (NULL);
	return (start_of_str);
}


/**
 * _strdup - duplicates a string.
 * @string: string to be duplicated
 * Return: string duplicate
 */
char *_strdup(const char *string)
{

	char *duplicate, *copy;
	size_t length;
	const char *temp;

	if (string == NULL)
		return (NULL);

	length = 0;
	temp = string;

	while (*temp++)
	{
		length++;
	}

	duplicate = (char *)malloc((length + 1) * sizeof(char));
	if (duplicate == NULL)
		return (NULL);

	copy = duplicate;
	while (*string)
	{
		*copy++ = *string++;
	}

	*copy = '\0';

	return (duplicate);
}







/**
 * _strlen - calculates and returns the length of the input string
 * @string: input string parameter
 * Return: length of the input string
 */
int _strlen(const char *string)
{
	int length = 0;

	while (string[length] != '\0')
	{
		length++;
	}

	return (length);
}
