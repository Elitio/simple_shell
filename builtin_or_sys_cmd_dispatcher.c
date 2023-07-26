#include "main.h"



/**
 * exec_line -  dispatcher for handling built-in commands and external
 * commands(system commands).
 * @shell_data: structure parameter
 * Return: 1 for no command or 0 if the command is executed successfully,
 */
int exec_line(data_shell *shell_data)
{
	char *command_str = shell_data->args[0];
	int (*builtin)(data_shell *shell_data) = get_builtin(command_str);

	if (command_str == NULL || shell_data->args == NULL)
		return (1);

	if (builtin != NULL)
		return (builtin(shell_data));
	else
		return (cmd_exec(shell_data));
}


