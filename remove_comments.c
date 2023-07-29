#include "main.h"

/**
 * remCommentF - deletes any  comment from user input
 *
 * @input_str: input string parameter
 * Return: input with no comments
 */
char *remCommentF(char *input_str)
{
	int i = 0, limit = 0;
	char nul_term = '\0';

	while (input_str[i])
	{
		switch (input_str[i])
		{
			case '#':
				if (i == 0)
				{
					free(input_str);
					return (NULL);
				}
				switch (input_str[i - 1])
				{
					case ' ':
						limit = i;
						break;
					case '\t':
						limit = i;
						break;
					case ';':
						limit = i;
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
		i++;
	}
	if (limit != 0)
	{
		input_str = reallocFnc(input_str, i, limit + 1);

		input_str[limit] = nul_term;
	}
	return (input_str);
}
