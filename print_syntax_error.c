#include "main.h"

/**
 * print_syntax_error - prints errors when parsing the input commands
 * @shell_data: structure parameter
 * @inp_str: input command string parameter
 * @ind: current char index parameter
 * @isSingle: flag to determine whether it is the first or second semicolon
 * Return: nothing
 */
void print_syntax_error(data_shell *shell_data, char *inp_str, int ind,int isSingle)
{
	char *char_holder = NULL, *err1_msg = ": Not found\n";
	char *err2_msg = "\" caused error\n", *err_full;
	char *cmdNum = aux_itoa(shell_data->counter);
	int err_len;

	switch (inp_str[ind])
	{
		case ';':
			char_holder = (isSingle == 0 ? (inp_str[ind + 1]
						== ';' ? ";;" : ";")
					: (inp_str[ind - 1] == ';'
						? ";;" : ";"));
			break;
		case '|':
			char_holder = (inp_str[ind + 1] == '|' ? "||" : "|");
			break;
		case '&':
			char_holder = (inp_str[ind + 1] == '&' ? "&&" : "&");
			break;
	}
	if (char_holder != NULL)
	{
		err_len = _strlen(shell_data->av[0]) + _strlen(cmdNum)
			+ _strlen(char_holder) + _strlen(err1_msg)
			+ _strlen(err2_msg) + 2;
		err_full = malloc(sizeof(char) * (err_len + 1));

		if (err_full != NULL)
		{
			_strcpy(err_full, shell_data->av[0]);
			_strcat(err_full, ": ");
			_strcat(err_full, cmdNum);
			_strcat(err_full, err1_msg);
			_strcat(err_full, char_holder);
			_strcat(err_full, err2_msg);
			write(STDERR_FILENO, err_full, err_len);
			free(err_full);
		}
	}
	free(cmdNum);
}
