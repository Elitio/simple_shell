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

/**
 * add_nodes - add separators and command lines in the lists
 *
 * @head_s: head of separator list
 * @head_l: head of command lines list
 * @input: input string
 * Return: no return
 */
void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int i = 0;
	char *line;

	input = swap_char(input, 0);

	while (input[i] != '\0')
	{
		if (input[i] == ';')
		{
			add_sep_node_end(head_s, input[i]);
			i++;
		}
		else if (input[i] == '|' || input[i] == '&')
		{
			add_sep_node_end(head_s, input[i]);
			i += 2;
		}
		else
		{
			i++;
		}
	}

	line = _strtok(input, ";|&");
	while (line != NULL)
	{
		line = swap_char(line, 1);
		add_line_node_end(head_l, line);
		line = _strtok(NULL, ";|&");
	}
}
