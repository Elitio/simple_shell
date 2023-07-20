#include "main.h"

/**
 * set_data - sets info of structure members
 *
 * @shell_data: structure parameter
 * @arg_vector: argument vector parameter
 * Return: nothing
 */
void set_data(data_shell *shell_data, char **arg_vector)
{

	unsigned int counter = 0;

	shell_data->av = arg_vector;

	shell_data->input = NULL;
	shell_data->args = NULL;

	shell_data->status = 0;
	shell_data->counter = 1;


	while (environ[counter])
	{
		counter++;
	}
	shell_data->_environ = malloc(sizeof(char *) * (counter + 1));

	counter = 0;

	while (environ[counter])
	{
		shell_data->_environ[counter] = _strdup(environ[counter]);
		counter++;
	}

	shell_data->_environ[counter] = NULL;
	shell_data->pid = aux_itoa(getpid());
}




/**
 * free_data - frees data structure
 *
 * @shell_data: structure parameter
 * Return: nothing
 */
void free_data(data_shell *shell_data)
{
	unsigned int counter_var = 0;

	while (shell_data->_environ[counter_var])
	{
		free(shell_data->_environ[counter_var]);
		counter_var++;
	}


	free(shell_data->_environ);

	free(shell_data->pid);
}
