include "main.h"

/**
 * without_comment - deletes comments from the input
 *
 * @in: input string
 * Return: input without comments
 */
char *without_comment(char *in)
{
	int i, limit;

	limit = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == ';' || in[i - 1] == '\t')
			{
				limit = i;
			}
		}
	}
	if (limit != 0)
	{
		char *new_in = malloc(limit + 1);
		if (new_in == null)
		{
			free(in);
			return (NULL);
		}

		memcpy(new_in, in, limit);
		new_in[limit] = '\0';

		free(in);
		in = new_in;
	}
	return (in);
}
