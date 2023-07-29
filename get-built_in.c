#include "main.h"

/**
 * isBuiltInF - Get the function pointer of a built-in command
 *
 * @cmd: The command name.
 * Return: Function pointer of the built-in command.
 */


int (*isBuiltInF(char *cmd))(data_shell *)
{
	int i;

	builtin_t builtin[] = {
		{ "unsetenv", _unsetenv },
		{ "cd", cdHandlerF },
		{ "env", _env },
		{ "exit", extShFnc },
		{ "setenv", _setenv },
		{ NULL, NULL }
	};

	if (cmd == NULL || *cmd == '\0')
	{

		return (NULL);
	}

	for (i = 0; builtin[i].name; i++)
	{
		if (builtin[i].name != NULL && cpmStrF(builtin[i].name,
					cmd) == 0)
		{
			return (builtin[i].f);
		}
	}

	return (NULL);
}




