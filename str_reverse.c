#include "main.h"



/**
 * strRevF - reverses a string
 * @string: input string parameter
 * Return: nothing
 */
void strRevF(char *string)
{
	int count = 0;
	char *start = string;
	char *end = string;
	char temp;

	while (*end != '\0')
	{
		count++;
		end++;
	}

	end--;

	while (start < end)
	{
		temp = *start;
		*start = *end;
		*end = temp;

		start++;

		end--;
	}
}

