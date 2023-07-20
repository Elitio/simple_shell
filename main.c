#include "main.h"

/**
 * main - main start point of shell program
 *
 * @arg_count: number of argument parameter
 * @arg_vector: array of arguments parameter
 * Return: 0 on success or 98 otherwise.
 */
int main(int arg_count, char **arg_vector)
{
	int stat_check = 0;
	data_shell shell_data;
	int error_code = 98;

	(void) arg_count;

	signal(SIGINT, get_sigint);

	set_data(&shell_data, arg_vector);

	shell_loop(&shell_data);


	free_data(&shell_data);

	if (shell_data.status < stat_check)
	{
		return (error_code);
	}


	return (shell_data.status);
}
