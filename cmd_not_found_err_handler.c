#include "main.h"

/**
 * errNotFoundF -  creates a custom error message indicating that the
 * specified command was not found in the shell
 * @shell_data: structure parameter
 * Return: the error message
 */
char *errNotFoundF(data_shell *shell_data)
{
<<<<<<< HEAD
	char *prg_ver_str = aux_itoa(shell_data->counter);
	char *err_str_msg = ": not found\n";
	int arg_mgs = strlen(shell_data->args[0]);
        char dir_err_mgs = ": No such file or directory\n";
	int dir_mgs_len = strlen(dir_err_mgs);
	int total_length = arg_mgs + dir_mgs_len;
	int index = 0;
	int i;
	int buff_len = _strlen(shell_data->av[0]) + get_len(shell_data->counter) + _strlen(shell_data->args[0]) + 16;
	char *err_str = malloc(sizeof(char) * (buff_len + 1));
	
	if (access(shell_data->args[0], X_OK) == -1)
	{
		write(STDERR_FILENO, "No such file or directory\n", sizeof(dir_err_mgs));
		_exit(EXIT_FAILURE);
	}
	if (opendir(shell_data->args[0]) == NULL)
	{
		strncpy(error_message, shell_data->args[0], strlen(shell_data->args[0]));
		strncpy(error_message, dir_err_mgs, strlen(dir_err_mgs));
		write(STDERR_FILENO,error_message, sizeof(total_length));
		_exit(EXIT_FAILURE);
	}

	if (err_str == NULL)
	{
		free(prg_ver_str);
		return (NULL);
	}

	for (i = 0; shell_data->av[0][i]; i++)
	{
		err_str[index++] = shell_data->av[0][i];
	}
	err_str[index++] = ':';
	err_str[index++] = ' ';
	for (i = 0; prg_ver_str[i]; i++)
	{
		err_str[index++] = prg_ver_str[i];
	}
	err_str[index++] = ':';
	err_str[index++] = ' ';
	for (i = 0; shell_data->args[0][i]; i++)
	{
		err_str[index++] = shell_data->args[0][i];
	}
	for (i = 0; err_str_msg[i]; i++)
	{
		err_str[index++] = err_str_msg[i];
	}
	err_str[index] = '\0';
	free(prg_ver_str);

	return (err_str);

char *prg_vs = aux_itoa(shell_data->counter), *err_m = ": not found\n";
=======
char *prg_vs = intToStrF(shell_data->counter), *err_m = ": not found\n";
>>>>>>> 7e01dd08841c6f7e3ea08efa920b9d4f15812632
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


