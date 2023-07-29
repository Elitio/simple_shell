#include "main.h"

/**
 * cdErrorFun - generate an error message when there is an issue with the cd
 * (change directory) command
 * @shell_data: structure parameter
 * Return: the error message
 */
char *cdErrorFun(data_shell *shell_data)
{
	int buff_len, ref_len;
	char *err_str_ptr;
	char *err_str, *prg_ver_str, *err_str_msg;

	prg_ver_str = intToStrF(shell_data->counter);
	if (shell_data->args[1][0] == '-')
	{
		err_str_msg = ": Oops! wrong option";
		ref_len = 2;
	}
	else
	{
		err_str_msg = ": can't cd to ";
		ref_len = lenStrF(shell_data->args[1]);
	}
	buff_len = lenStrF(shell_data->av[0]) + lenStrF(shell_data->args[0])
		+ lenStrF(prg_ver_str) + lenStrF(err_str_msg) + ref_len + 5;
	err_str = malloc(sizeof(char) * (buff_len + 1));
	if (err_str == NULL)
	{
		free(prg_ver_str);
		return (NULL);
	}
	err_str_ptr = err_str;
	cpyStrF(err_str_ptr, shell_data->av[0]);
	catStrF(err_str_ptr, ": ");
	catStrF(err_str_ptr, prg_ver_str);
	catStrF(err_str_ptr, ": ");
	catStrF(err_str_ptr, shell_data->args[0]);
	catStrF(err_str_ptr, err_str_msg);
	if (shell_data->args[1][0] == '-')
	{
		catStrF(err_str_ptr, shell_data->args[1]);
	}
	catStrF(err_str_ptr, shell_data->args[1]);
	catStrF(err_str_ptr, "\n");
	catStrF(err_str_ptr, "\0");
	free(prg_ver_str);
	return (err_str_ptr);
}


