#include "main.h"




/**
 * get_error - determines the type of error based on the input error code int
 * value and calls corresponding error handling functions to
 * retrieve the appropriate error messages.
 * @shell_data: structure parameter
 * @error_ref: error reference value parameter
 * Return: error reference code
 */
int get_error(data_shell *shell_data, int error_ref)
{
	char *error;

	error = NULL;


	if (error_ref == -1)
		error = error_env(shell_data);
	else if (error_ref == 126)
		error = error_path_126(shell_data);
	else if (error_ref == 127)
		error = error_not_found(shell_data);

	else if (error_ref == 2)
	{
		if (_strcmp("exit", shell_data->args[0]) == 0)
			error = error_exit_shell(shell_data);
		else if (_strcmp("cd", shell_data->args[0]) == 0)
			error = error_get_cd(shell_data);
	}


	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));

		free(error);
	}


	shell_data->status = error_ref;

	return (error_ref);

}
