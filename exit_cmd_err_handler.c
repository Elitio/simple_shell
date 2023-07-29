#include "main.h"

/**
 * error_exit_shell - generates an error message for an illegal number argument
 * passed to the exit command in the shell
 * @shell_data: structure parameter
 * Return: the error message
 */
char *error_exit_shell(data_shell *shell_data)
{
	char *prg_ver_str = aux_itoa(shell_data->counter);
	int prog_len = 0, i;
	int prg_ver_len = 0, cmd_len = 0, arg_len = 0;
	char *err_str;
	int offset = 0, err_msg_len;

	while (shell_data->av[0][prog_len])
		prog_len++;
	while (prg_ver_str[prg_ver_len])
		prg_ver_len++;
	while (shell_data->args[0][cmd_len])
		cmd_len++;
	while (shell_data->args[1][arg_len])
		arg_len++;
	err_msg_len = prog_len + prg_ver_len + cmd_len + arg_len + 23;
	err_str = malloc(sizeof(char) * (err_msg_len + 1));
	if (err_str == NULL)
	{
		free(prg_ver_str);
		return (NULL);
	}
	for (i = 0; i < prog_len; i++)
		err_str[offset++] = shell_data->av[0][i];
	err_str[offset++] = ':';
	err_str[offset++] = ' ';
	for (i = 0; i < prg_ver_len; i++)
		err_str[offset++] = prg_ver_str[i];
	err_str[offset++] = ':';
	err_str[offset++] = ' ';
	for (i = 0; i < cmd_len; i++)
		err_str[offset++] = shell_data->args[0][i];
	for (i = 0; i < 19; i++)
		err_str[offset++] = ": Illegal number: "[i];
	for (i = 0; i < arg_len; i++)
		err_str[offset++] = shell_data->args[1][i];
	err_str[offset++] = '\n';
	err_str[offset] = '\0';

	free(prg_ver_str);
	return (err_str);
}
