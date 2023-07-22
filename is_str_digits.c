#include "main.h"

/**
 * _isdigit - check if a given string contains only digit characters (ie. 0-9).
 * @string: input string
 * Return: 1 if the string contains only digits. 0 otherwise.
 */
int _isdigit(const char *string)
{
	unsigned int count = 0;

	while (string[count] != '\0')
	{
		if (string[count] < '0' || string[count] > '9')
			return (0);

		count++;
	}

	return (1);

}
