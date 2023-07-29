#include "main.h"

/**
 * errNotFoundF -  creates a custom error message indicating that the
 * specified command was not found in the shell
 * @shell_data: structure parameter
 * Return: the error message
 */
char *errNotFoundF(data_shell *shell_data)
{
char *prg_vs = intToStrF(shell_data->counter), *err_m = ": not found\n";
int index = 0, i;
int buff_len = lenStrF(shell_data->av[0]) + lenGetF(shell_data->counter)
	+ lenStrF(shell_data->args[0]) + 16;
char *err_str = malloc(sizeof(char) * (buff_len + 1));

if (access(shell_data->args[0], X_OK) == -1)
{
	write(STDERR_FILENO, "No such file or directory\n",
		sizeof("No such file or directory\n"));
	_exit(EXIT_FAILURE);
}
if (err_str == NULL)
{
	free(prg_vs);
	return (NULL);
}
for (i = 0; shell_data->av[0][i]; i++)
{
	err_str[index++] = shell_data->av[0][i];
}
err_str[index++] = ':';
err_str[index++] = ' ';
for (i = 0; prg_vs[i]; i++)
{
	err_str[index++] = prg_vs[i];
}
err_str[index++] = ':';
err_str[index++] = ' ';
for (i = 0; shell_data->args[0][i]; i++)
{
	err_str[index++] = shell_data->args[0][i];
}
for (i = 0; err_m[i]; i++)
{
	err_str[index++] = err_m[i];
}
err_str[index] = '\0';
free(prg_vs);
return (err_str);
}


