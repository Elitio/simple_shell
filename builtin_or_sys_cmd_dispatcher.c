#include "main.h"



/**
 * exec_line -  dispatcher for handling built-in commands and external
 * commands(system commands).
 * @shell_data: data relevant (args)
 * Return: 1 for no command or 0 if the command is executed successfully,
 */
int exec_line(data_shell *shell_data)
{

	char *command_str = shell_data->args[0];

	 int (*builtin)(data_shell *shell_data) = get_builtin(command_str);


	if (command_str == NULL)

		return (1);


	switch (builtin != NULL)
	{
		case 1:

			return (builtin(shell_data));
		default:
			return (cmd_exec(shell_data));
	}
}
