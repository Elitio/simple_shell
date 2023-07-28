#include "main.h"

/**
 * error_not_found -  creates a custom error message indicating that the
 * specified command was not found in the shell
 * @shell_data: structure parameter
 * Return: the error message
 */
char *error_not_found(data_shell *shell_data)
{
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
}


