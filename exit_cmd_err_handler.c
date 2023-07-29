#include "main.h"

/**
 * error_exit_shell - generates an error message for an illegal number argument
 * passed to the exit command in the shell
 * @shell_data: structure parameter
 * Return: the error message
 */
char *error_exit_shell(data_shell *shell_data)
{
	char *ver_str;
	int ver_len, arg0_len, arg1_len, total_len;
	int av_len = _strlen(shell_data->av[0]);
	char *errorMs;

	ver_str = aux_itoa(shell_data->counter);
	ver_len = _strlen(ver_str);
	arg0_len = _strlen(shell_data->args[0]);
	arg1_len = _strlen(shell_data->args[1]);
	total_len = av_len + ver_len
	+ arg0_len + arg1_len + 23;

	errorMs = malloc(sizeof(char) * (total_len + 1));
	if (errorMs == NULL)
	{
		free(ver_str);
		return (NULL);
	}

	_strcpy(errorMs, shell_data->av[0]);
	_strcat(errorMs, ": ");
	_strcat(errorMs, ver_str);
	_strcat(errorMs, ": ");
	_strcat(errorMs, shell_data->args[0]);
	_strcat(errorMs, ": Illegal number: ");
	_strcat(errorMs, shell_data->args[1]);
	_strcat(errorMs, "\n");
	_strcat(errorMs, "\0");
	free(ver_str);
	return (errorMs);
}
