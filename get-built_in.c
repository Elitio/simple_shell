#include "main.h"

/**
 * get_builtin - Get the function pointer of a built-in command
 *
 * @cmd: The command name.
 * Return: Function pointer of the built-in command.
 */

int (*get_builtin(char *cmd))(data_shell *)
{
	int i;

	builtin_t builtin[] = {
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell },
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ NULL, NULL }
	};
	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, cmd) == 0)
		{
			return (builtin[i].f);
		}
	}
	return (NULL);
}
