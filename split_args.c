#include "main.h"

/**
 * custom_swap - Will swap & and | for non print characters.
 * @input: in put string.
 * @option: characters equivalent ASCII character.
 *
 * Return: Wil return the swapped string.
 */

char *custom_swap(char *input, int option)
{
	int i = 0;

	switch (option)
	{
		case 0:
			while (input[i] != '\0')
			{
				if (input[i] == '|')
				{
					if (input[i + 1] != '|')
					{
						input[i] = 16;
					}
					else
					{
						i++;
					}
				}

				if (input[i] == '&')
				{
					if (input[i + 1] != '&')
					{
						input[i] = 12;
					}
					else
					{
						i++;
					}
				}
				i++;
			}
			break;

		default:
			while (input[i] != '\0')
			{
				input[i] = (input[i] == 16 ? '|' : input[i]);
				input[i] = (input[i] == 12 ? '&' : input[i]);
				i++;
			}
	}

	return (input);
}
