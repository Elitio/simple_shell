#include "main.h"




/**
 * _unsetenv - removes the environment variable specified as an argument
 * from the shell's environment if it exists
 * @shell_data: data relevant (env name)
 *
 * Return: 1 on success.
 */

int _unsetenv(data_shell *shell_data)
{
	int ind = 0, j;
	char *env_var_check, *env_name_check;

	if (!shell_data->args[1])
	{
		get_error(shell_data, -1);
		return (1);
	}

	while (shell_data->_environ[ind])
	{
		env_var_check = _strdup(shell_data->_environ[ind]);
		env_name_check = strtok(env_var_check, "=");

		if (_strcmp(env_name_check, shell_data->args[1]) == 0)
		{
			free(shell_data->_environ[ind]);

			j = ind;
			while (shell_data->_environ[j])
			{
				shell_data->_environ[j]
					= shell_data->_environ[j + 1];
				j++;
			}
			break;
		}

		free(env_var_check);
		ind++;
	}

	return (1);
}

