#include "main.h"




/**
 * getErrorF - determines the type of error based on the input error code int
 * value and calls corresponding error handling functions to
 * retrieve the appropriate error messages.
 * @shell_data: structure parameter
 * @error_ref: error reference value parameter
 * Return: error reference code
 */
int getErrorF(data_shell *shell_data, int error_ref)
{
	char *error_ret = NULL;



	if (error_ref == -1)
		error_ret = envErrorF(shell_data);
	else if (error_ref == 126)
		error_ret = error126F(shell_data);
	else if (error_ref == 127)
		error_ret = errNotFoundF(shell_data);

	else if (error_ref == 2)
	{
		if (cpmStrF("exit", shell_data->args[0]) == 0)
			error_ret = exitShErrorF(shell_data);
		else if (cpmStrF("cd", shell_data->args[0]) == 0)
			error_ret = cdErrorFun(shell_data);
	}


	if (error_ret != NULL)
	{
		write(STDERR_FILENO, error_ret, lenStrF(error_ret));

		free(error_ret);
	}


	shell_data->status = error_ref;

	return (error_ref);

}
