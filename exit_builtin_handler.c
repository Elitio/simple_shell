#include "main.h"



/**
 * extShFnc - handles the behavior of the "exit" command.
 * @shell_data: structure parameter
 * Return: 0 on success otherwise 1 to indicate an error.
 */
int extShFnc(data_shell *shell_data)
{
	unsigned int stat_val = 0;
	int count;
	char *arg_str = shell_data->args[1];

	if (arg_str != NULL)
	{

		for (count = 0; arg_str[count] != '\0'; count++)
		{
			if (arg_str[count] < '0' || arg_str[count] > '9')
			{
				getErrorF(shell_data, 2);
				shell_data->status = 2;
				return (1);
			}
			stat_val = stat_val * 10 + (arg_str[count] - '0');
		}

		if (stat_val > INT_MAX)
		{
			getErrorF(shell_data, 2);
			shell_data->status = 2;
			return (1);
		}

		shell_data->status = stat_val % 256;
	}

	return (0);
}

