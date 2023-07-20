#include "holberton.h"

/**
 * shell_loop - Loop to prompt user for input
 * @data_shell_info: structure info parameter
 * Return: no return.
 */

void shell_loop(data_shell *data_shell_info)
{
	int counter = 1;
	char *user_input;
	int is_end_of_file;

	do {

		write(STDOUT_FILENO, "$ ", 2);

		user_input = read_line(&is_end_of_file);
		if (is_end_of_file != -1)
		{
			user_input = without_comment(user_input);
			if (user_input == NULL)
				continue;

			switch (check_syntax_error(data_shell_info, user_input))
			{
				case 1:
					data_shell_info->status = 2;
					free(user_input);
					continue;
				default:
					break;
			}

			user_input = rep_var(user_input, data_shell_info);
			counter = split_commands(data_shell_info, user_input);
			data_shell_info->counter += 1;
			free(user_input);
		}
		else
		{
			counter = 0;

			free(user_input);
		}
	} while (counter == 1);
}
