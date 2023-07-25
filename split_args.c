#include "holberton.h"



/**
 * swap_char - performs character swapping based on the value of
 * the isZero parameter.
 * @inp_str: string input parameter
 * @isZero: int check for zero or non-zero to specify swap type
 * Return: final swapped string
  */
char *swap_char(char *inp_str, int isZero)
{
	int ind;

	if (isZero == 0)
	{
		ind = 0;
		while (inp_str[ind])
		{
			if (inp_str[ind] == '|')
			{
				if (inp_str[ind + 1] != '|')
					inp_str[ind] = 16;
				else
					ind++;
			}

			if (inp_str[ind] == '&')
			{
				if (inp_str[ind + 1] != '&')
					inp_str[ind] = 12;
				else
					ind++;
			}
			ind++;
		}
	}
	else
	{
		ind = 0;
		while (inp_str[ind])
		{
			inp_str[ind] = (inp_str[ind] == 16 ? '|' : inp_str[ind]);
			inp_str[ind] = (inp_str[ind] == 12 ? '&' : inp_str[ind]);

			ind++;
		}
	}
	return (inp_str);
}













/**
 * add_nodes - parses and adds nodes to 2 linked lists.
 * @sepHead: pointer to head of separator linked list
 * @cmdHead: pointer to head of command line linked list
 * @inp_str: string input parameter
 * Return: nothing
 */
void add_nodes(sep_list **sepHead, line_list **cmdHead, char *inp_str)
{
	char *sep_or_delim = ";|&";
	char *token = _strtok(inp_str, sep_or_delim);
	char delim;

	inp_str = swap_char(inp_str, 0);

	while (token != NULL)
	{
		token = swap_char(token, 1);
		add_line_node_end(cmdHead, token);
		delim = inp_str[token - inp_str + _strlen(token)];
		if (delim == ';' || delim == '|' || delim == '&')
			add_sep_node_end(sepHead, delim);
		token = _strtok(NULL, sep_or_delim);
	}
}




/**
 * go_next - navigate through linked lists of sep_list and line_list nodes
 * based on the exit status (datash->status) of the previous command execution
 * @sepHead: Pointer to the head of the sep_list linked list parameter
 * @cmdHead: Pointer to the head of the line_list linked list.
 * @shell_data: structure parameter
 * Return: nothing
 */
void go_next(sep_list **sepHead, line_list **cmdHead, data_shell *shell_data)
{
	int loop = 1, ext_stat;
	sep_list *tempSepHead = *sepHead;
	line_list *tempCmdHead = *cmdHead;

	while (tempSepHead != NULL && loop)
	{
		ext_stat = (shell_data->status == 0) ? 0 : 1;
		if ((tempSepHead->separator == '&' && ext_stat == 0) ||
				(tempSepHead->separator == '|' && ext_stat
				 == 1))
		{
			loop = 0;
		}

		tempCmdHead = (tempSepHead->separator == '|')
			? tempCmdHead->next : tempCmdHead;
		tempSepHead = tempSepHead->next;
	}

	*sepHead = tempSepHead;
	*cmdHead = tempCmdHead;
}



/**
 * split_commands - splits and executes multiple commands
 * separated by separators like ;, |, or &
 * @shell_data: data structure
 * @inp_str: string input parameter
 * Return: 0 to stop executing or 1 to continue executing
 * more commands.
 */
int split_commands(data_shell *shell_data, char *inp_str)
{
	sep_list *sepHead = NULL, *tempSepHead;

	line_list *cmdHead = NULL, *tempCmdHead;

	int loop = 1;

	add_nodes(&sepHead, &cmdHead, inp_str);
	tempSepHead = sepHead;
	tempCmdHead = cmdHead;


	do {
		shell_data->input = tempCmdHead->line;

		shell_data->args = split_line(shell_data->input);

		loop = exec_line(shell_data);
		free(shell_data->args);


		go_next(&tempSepHead, &tempCmdHead, shell_data);

		if (tempCmdHead)
			tempCmdHead = tempCmdHead->next;

	} while (tempCmdHead && loop);

	free_sep_list(&sepHead);

	free_line_list(&cmdHead);

	return (loop);
}







/**
 * split_line - splitting a given string (input) into an array
 * of tokens based on a specified delimiter
 * @inp_str: string input parameter.
 * Return:  dynamically allocated array of tokens
 */
char **split_line(char *inp_str)
{
	size_t _sizeBuff = TOK_BUFSIZE;

	size_t cur_ind = 0;

	char **toks = malloc(sizeof(char *) * _sizeBuff);
	char *frst_tok;

	if (toks == NULL)
	{
		write(STDERR_FILENO, ": Oops! couldn't allocate memory\n", 32);

		exit(EXIT_FAILURE);
	}

	do {
		frst_tok = _strtok(inp_str, TOK_DELIM);

		if (cur_ind == _sizeBuff)
		{
			_sizeBuff += TOK_BUFSIZE;

			toks = _reallocdp(toks, cur_ind, sizeof(char *)
					* _sizeBuff);
			if (toks == NULL)
			{
				write(STDERR_FILENO, ": memory error\n", 14);

				exit(EXIT_FAILURE);
			}
		}

		toks[cur_ind++] = frst_tok;

		inp_str = NULL;

	} while (frst_tok != NULL);

	toks[cur_ind] = NULL;
	return (toks);
}
