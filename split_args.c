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

/**
 * go_next - Go to the next command line stored.
 *
 * @list_s: separator lists of args.
 * @list_l: command line lists of args.
 * @datash: customized data structure.
 * Return: void.
 */

void go_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int loop_sep = 1;
	sep_list *current_sep = *list_s;
	line_list *current_line = *list_l;

	while (current_sep != NULL && loop_sep)
	{
		if (datash->status == 0)
		{
			if (current_sep->separator == '&' || current_sep->separator == ';')
			{
				loop_sep = 0;
			}
			else if (current_sep->separator == '&')
			{
				current_line = current_line->next;
				current_sep = current_sep->next;
			}
		}
		else
		{
			if (current_sep->separator == '|' || current_sep->separator == ';')
			{
				loop_sep = 0;
			}
			else if (current_sep->separator == '&')
			{
				current_line = current_line->next;
				current_sep = current_sep->next;
			}
		}

		if (current_sep != NULL && !loop_sep)
		{
			current_sep = current_sep->next;
		}
	}

	*list_s = current_sep;
	*list_l = current_line;
}

/**
 * split_commands - Will splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @datash: data structure
 * @input: input string
 * Return: 0 will exit, 1 to continue.
 */

int split_commands(data_shell *datash, char *input)
{

	sep_list *head_s, *list_s;

	line_list *head_l, *list_l;

	int loop;


	head_s = NULL;

	head_l = NULL;


	add_nodes(&head_s, &head_l, input);


	list_s = head_s;

	list_l = head_l;


	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = split_line(datash->input);
		loop = exec_line(datash);
		free(datash->args);

		if (loop == 0)
		{
			break;
		}

		if (datash->status == 0)
		{
			if (list_s->separator == ';' || list_s->separator == '|')
			{
				go_next(&list_s, &list_l, datash);
			}
		}
		else
		{
			if (list_s->separator == '|' || list_s->separator == ';')
			{
				go_next(&list_s, &list_l, datash);
			}

			if (list_l != NULL)
			{
				list_l = list_l->next;
			}
		}


		free_sep_list(&head_s);
		free_line_list(&head_l);

		if (loop == 0)
		{
			return (0);
		}
		return (1);
}

/**
 * split_line - tokenizes the input string
 *
 * @input: input string.
 * Return: string splitted.
 */

char **split_line(char *input)
{
	size_t bsize = TOK_BUFSIZE;
	size_t i = 0;
	char **tokens = malloc(sizeof(char *) * bsize);

	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	char *token = strtok(input, TOK_DELIM);
	tokens[i++] = token;

	while (token != NULL)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			char **temp = realloc(tokens, sizeof(char *) * bsize);
			if (temp == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
			tokens = temp;
		}

		token = strtok(NULL, TOK_DELIM);
		tokens[i++] = token;
	}

	return (tokens);
}
