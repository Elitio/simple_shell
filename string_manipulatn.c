#include "main.h"






/**
 * _strcmp - compares two strings.
 * @first_str: type str compared
 * @second_str: type str compared
 * Return: 1 if first_str is greater than second_str
 * and 0 if both strings are equal.
 */



int _strcmp(char *first_str, char *second_str)
{
	int count = 0;
	int result = 0;

	while (first_str[count] != '\0' && second_str[count] != '\0' &&
			first_str[count] == second_str[count])
	{
		count++;
	}

	if (first_str[count] > second_str[count])
		result = 1;
	else if (first_str[count] < second_str[count])
		result = -1;

	return (result);
}



/**
 * _strspn -  it calculates the length of the initial segment of a string
 * consisting of only characters present in another string
 * @string: string to work on.
 * @checkn_str: string to check for characters
 * Return: length of the substring found so far.
 */
int _strspn(char *string, char *checkn_str)
{
	int i = 0, j;

	while (string[i])
	{
		j = 0;
		while (checkn_str[j])
		{
			if (string[i] == checkn_str[j])
				break;
			j++;
		}

		if (!checkn_str[j])
			break;

		i++;
	}

	return (i);
}



/**
 * _strcat - concatenate or joins two strings
 * @str_dest: string to which other string would be joined to
 * @str_source: string joining other string parameter
 * Return: the combined or final string
 */
char *_strcat(char *str_dest, const char *str_source)
{
	int count1 = 0;
	int count2 = 0;

	while (str_dest[count1] != '\0')
	{
		count1++;
	}

	while (str_source[count2] != '\0')
	{
		str_dest[count1] = str_source[count2];
		count1++;
		count2++;
	}

	str_dest[count1] = '\0';

	return (str_dest);
}





/**
 * _strchr - searches for the first occurrence of a character in a string.
 * @string: string.
 * @charac: character.
 * Return: a pointer to the location of that character.
 */
char *_strchr(char *string, char charac)
{
	while (*string != '\0')
	{
		if (*string == charac)
			return ((char *)string);
		string++;
	}

	if (*string == charac)
		return ((char *)string);

	return (NULL);
}


/**
 * *_strcpy - Copies a string to another string
 * @str_dest: buffer other string is to be copied to
 * @str_source: string buffer to copy to the other
 * Return: the final string
 */
char *_strcpy(char *str_dest, char *str_source)
{
	size_t count = 0;

	while (str_source[count] != '\0')
	{
		str_dest[count] = str_source[count];
		count++;
	}
	str_dest[count] = '\0';

	return (str_dest);
}

