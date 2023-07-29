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

	signal(SIGINT, getSigF);

	setDataF(&shell_data, arg_vector);

	sh_loopF(&shell_data);


	freeDataF(&shell_data);

	if (shell_data.status < stat_check)
	{
		return (error_code);
	}


	return (shell_data.status);
}
