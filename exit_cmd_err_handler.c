#include "main.h"

/**
 * error_exit_shell - generates an error message for an illegal number argument
 * passed to the exit command in the shell
 * @shell_data: structure parameter
 * Return: the error message
 */
char *error_exit_shell(data_shell *shell_data)
{
	char *ver_str = aux_itoa(shell_data->counter);
	int av_len = _strlen(shell_data->av[0]);
	char *error_pt, *errorMs;
	int ver_len = _strlen(ver_str);
	int arg0_len = _strlen(shell_data->args[0]);
	int arg1_len = _strlen(shell_data->args[1]);
	int total_len = av_len + ver_len
	+ arg0_len + arg1_len + 23;

	errorMs = malloc(sizeof(char) * (total_len + 1));
	if (errorMs == NULL)
	{
		free(ver_str);
		return (NULL);
	}

	error_ptr = errorMs;
	_strcpy(error_ptr, shell_data->av[0]);
	error_ptr += av_len;
	_strcpy(error_ptr, ": ");
	error_ptr += 2;
	_strcpy(error_ptr, ver_str);
	error_ptr += ver_len;
	_strcpy(error_ptr, ": ");
	error_ptr += 2;
	_strcpy(error_ptr, shell_data->args[0]);
	error_ptr += arg0_len;
	_strcpy(error_ptr, ": Illegal number: ");
	error_ptr += 20;
	_strcpy(error_ptr, shell_data->args[1]);
	error_ptr += arg1_len;
	_strcpy(error_ptr, "\n\0");

	free(ver_str);
	return (errorMs);
}
