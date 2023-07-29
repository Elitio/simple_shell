#include "main.h"

/**
 * printInError - prints errors when parsing the input commands
 * @shell_data: structure parameter
 * @inp_str: input command string parameter
 * @ind: current char index parameter
 * @isSingle: flag to determine whether it is the first or second semicolon
 * Return: nothing
 */
void printInError(data_shell *shell_data, char *inp_str, int ind,
		int isSingle)
{
	char *char_holder = NULL, *err1_msg = ": Not found\n";
	char *err2_msg = "\" caused error\n", *err_full;
	char *cmdNum = intToStrF(shell_data->counter);
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
		err_len = lenStrF(shell_data->av[0]) + lenStrF(cmdNum)
			+ lenStrF(char_holder) + lenStrF(err1_msg)
			+ lenStrF(err2_msg) + 2;
		err_full = malloc(sizeof(char) * (err_len + 1));

		if (err_full != NULL)
		{
			cpyStrF(err_full, shell_data->av[0]);
			catStrF(err_full, ": ");
			catStrF(err_full, cmdNum);
			catStrF(err_full, err1_msg);
			catStrF(err_full, char_holder);
			catStrF(err_full, err2_msg);
			write(STDERR_FILENO, err_full, err_len);
			free(err_full);
		}
	}
	free(cmdNum);
}
