#include "main.h"

/**
 * exitShErrorF - generates an error message for an illegal number argument
 * passed to the exit command in the shell
 * @shell_data: structure parameter
 * Return: the error message
 */
char *exitShErrorF(data_shell *shell_data)
{
	char *ver_str;
	int ver_len, arg0_len, arg1_len, total_len;
	int av_len = lenStrF(shell_data->av[0]);
	char *errorMs;

	ver_str = intToStrF(shell_data->counter);
	ver_len = lenStrF(ver_str);
	arg0_len = lenStrF(shell_data->args[0]);
	arg1_len = lenStrF(shell_data->args[1]);
	total_len = av_len + ver_len
	+ arg0_len + arg1_len + 23;

	errorMs = malloc(sizeof(char) * (total_len + 1));
	if (errorMs == NULL)
	{
		free(ver_str);
		return (NULL);
	}

	cpyStrF(errorMs, shell_data->av[0]);
	catStrF(errorMs, ": ");
	catStrF(errorMs, ver_str);
	catStrF(errorMs, ": ");
	catStrF(errorMs, shell_data->args[0]);
	catStrF(errorMs, ": Illegal number: ");
	catStrF(errorMs, shell_data->args[1]);
	catStrF(errorMs, "\n");
	catStrF(errorMs, "\0");
	free(ver_str);
	return (errorMs);
}
