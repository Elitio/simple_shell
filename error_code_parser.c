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
	char *error_ret = NULL;



	if (error_ref == -1)
		error_ret = error_env(shell_data);
	else if (error_ref == 126)
		error_ret = error_path_126(shell_data);
	else if (error_ref == 127)
		error_ret = error_not_found(shell_data);

	else if (error_ref == 2)
	{
		if (_strcmp("exit", shell_data->args[0]) == 0)
			error_ret = error_exit_shell(shell_data);
		else if (_strcmp("cd", shell_data->args[0]) == 0)
			error_ret = error_get_cd(shell_data);
	}


	if (error_ret != NULL)
	{
		write(STDERR_FILENO, error_ret, _strlen(error_ret));

		free(error_ret);
	}


	shell_data->status = error_ref;

	return (error_ref);

}
