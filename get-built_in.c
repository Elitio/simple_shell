#include "main.h"

/**
 * get_builtin - Get the function pointer of a built-in command
 *
 * @cmd: The command name.
 * Return: Function pointer of the built-in command.
 */

int (*get_builtin(char *cmd))(data_shell *)
{
	typedef struct
	{
		char *name;
		int (*f)(data_shell *);
	} builtin_t;

	builtin_t builtin[] =
	{
		{"env", env},
		{"exit", exit_shell},
		{"setenv", setenv_shell},
		{"unsetenv", unsetenv_shell},
		{"cd", cd_shell},
		{"help", get_help},
		{NULL, NULL}
	};

	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (strcmp(builtin[i].name, cmd) == 0)
		{
			break;
		}
	}

	return (builtin[i].f);
}
