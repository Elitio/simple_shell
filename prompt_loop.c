#include "main.h"

/**
 * sh_loopF - Loop to prompt user for input
 * @data_shell_info: structure info parameter
 * Return: no return.
 */

void sh_loopF(data_shell *data_shell_info)
{
	int count = 1;
	char *user_input;
	int the_end_of_file;

	do {
		write(STDIN_FILENO, "$ ", 2);
		user_input = callGetLineF(&the_end_of_file);
		if (the_end_of_file != -1)
		{
			user_input = remCommentF(user_input);
			if (user_input == NULL)
			{
				continue;
			}
			switch (chkInEror(data_shell_info, user_input))
			{
				case 1:
					data_shell_info->status = 2;
					free(user_input);
					continue;
					break;
				default:
					break;
			}

			user_input = repVarFnc(user_input, data_shell_info);
			count = spltCmdFunc(data_shell_info, user_input);
			data_shell_info->counter += 1;
		}
		else
		{
			count = 0;
		}
		free(user_input);
	} while (count == 1);
}

