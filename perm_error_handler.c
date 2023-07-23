#include "main.h"




/**
 * error_path_126 - generates an error message with details about a command
 * that could not be executed due to permission denied
 * @shell_data: data relevant (counter, arguments).
 *
 * Return: error message
 */
char *error_path_126(data_shell *shell_data)
{
	char *error_perm_msg = "Permission access failure";
	char *perm_er_str = aux_itoa(shell_data->counter);
	int buff_len = _strlen(shell_data->av[0]) + _strlen(perm_er_str)
		+ _strlen(shell_data->args[0]) + _strlen(error_perm_msg) + 4;
	char *error_str = malloc(sizeof(char) * (buff_len + 1));
	int count = 0, count_2 = 0;

	if (error_str == NULL)
	{
		free(error_str);
		free(perm_er_str);
		return (NULL);
	}
	while (shell_data->av[0][count] != '\0')
	{
		error_str[count_2] = shell_data->av[0][count];
		count++;
		count_2++;
	}
	error_str[count_2] = ':';
	count_2++;
	count = 0;
	while (perm_er_str[count] != '\0')
	{
		error_str[count_2] = perm_er_str[count];
		count++;
		count_2++;
	}
	error_str[count_2] = ':';
	count_2++;
	count = 0;
	while (error_perm_msg[count] != '\0')
	{
		error_str[count_2] = error_perm_msg[count];
		count++;
		count_2++;
	}
	error_str[count_2] = '\0';
	free(perm_er_str);
	return (error_str);
}

