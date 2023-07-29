#include "main.h"


/**
 * cdDotF - handles the cd command with the argument "."
 *
 * @shell_data: structure parameter
 * Return: no return
 */
void cdDotF(data_shell *shell_data)
{
	char *directory, *copied_current_dir, current_dir[PATH_MAX], *tok_dir;

	/* Get the current working directory and store it in 'current_dir' */
	getcwd(current_dir, sizeof(current_dir));
	copied_current_dir = dupStrF(current_dir);
	/* Set the environment variable "OLDPWD" to the copied current directory */
	set_env("OLDPWD", copied_current_dir, shell_data);
	directory = shell_data->args[1];
	switch (cpmStrF(".", directory))
	{
		case 0:
			set_env("PWD", copied_current_dir, shell_data);
			free(copied_current_dir);
			return;
		default:
			break;
	}
	switch (cpmStrF("/", copied_current_dir))
	{
		case 0:
			free(copied_current_dir);
			return;
		default:
			break;
	}
	tok_dir = copied_current_dir;
	strRevF(tok_dir);
	tok_dir = tokStrF(tok_dir, "/");
	if (tok_dir != NULL)
		tok_dir = tokStrF(NULL, "\0");
	if (tok_dir != NULL)
	{
		chdir(tok_dir);
		set_env("PWD", tok_dir, shell_data);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", shell_data);
	}
	shell_data->status = 0;
	free(copied_current_dir);
}








/**
 * cdPrevF - changes directory from the current one to the previous one
 *
 * @shell_data: structure parameter
 * Return: nothing
 */
void cdPrevF(data_shell *shell_data)
{
	char *new_current_dir, *prev_dir, current_dir[PATH_MAX];
	char *copied_current_dir;
	char *copied_prev_dir;

	getcwd(current_dir, sizeof(current_dir));
	copied_current_dir = dupStrF(current_dir);

	prev_dir = _getenv("OLDPWD", shell_data->_environ);

	switch (prev_dir != NULL)
	{
		case 0:
			copied_prev_dir = copied_current_dir;
			break;
		case 1:
			copied_prev_dir = dupStrF(prev_dir);
			break;
	}
	set_env("OLDPWD", copied_current_dir, shell_data);
	switch (chdir(copied_prev_dir))
	{
		case 0:
			set_env("PWD", copied_prev_dir, shell_data);
			break;
		case -1:
			set_env("PWD", copied_current_dir, shell_data);
			break;
	}
	new_current_dir = _getenv("PWD", shell_data->_environ);
	write(STDOUT_FILENO, new_current_dir, lenStrF(new_current_dir));
	write(STDOUT_FILENO, "\n", 1);
	free(copied_current_dir);
	if (prev_dir)
		free(copied_prev_dir);
	shell_data->status = 0;
}













/**
 * cdHomeF - changes directory from the current one to home directory
 *
 * @shell_data: structure parameter
 * Return: nothing
 */
void cdHomeF(data_shell *shell_data)
{
	char *copied_current_dir, current_dir[PATH_MAX], *home_dir;

	getcwd(current_dir, sizeof(current_dir));

	copied_current_dir = dupStrF(current_dir);

	home_dir = _getenv("HOME", shell_data->_environ);

	do {
		if (home_dir == NULL)
		{
			set_env("OLDPWD", copied_current_dir, shell_data);

			free(copied_current_dir);
			break;
		}

		if (chdir(home_dir) == -1)
		{
			getErrorF(shell_data, 2);
			free(copied_current_dir);
			break;
		}

		set_env("OLDPWD", copied_current_dir, shell_data);

		set_env("PWD", home_dir, shell_data);

		free(copied_current_dir);
		shell_data->status = 0;

	} while (0);
}


/**
 * cdToDirF - changes directory from the current one to the one specified
 *
 * @shell_data: structure parameter
 * Return: nothing
 */
void cdToDirF(data_shell *shell_data)
{
	char *directory, *copied_current_dir, current_dir[PATH_MAX];
	char *copied_spec_dir;

	getcwd(current_dir, sizeof(current_dir));

	directory = shell_data->args[1];

	if (chdir(directory) == -1)
	{
		getErrorF(shell_data, 2);

		return;
	}

	copied_current_dir = dupStrF(current_dir);
	copied_spec_dir = dupStrF(directory);

	set_env("OLDPWD", copied_current_dir, shell_data);

	set_env("PWD", copied_spec_dir, shell_data);

	free(copied_current_dir);

	free(copied_spec_dir);

	shell_data->status = 0;
}




/**
 * cdHandlerF - handles the cd command with or without args
 *
 * @data_shell: structure parameter
 * Return: 1 on success
 */
int cdHandlerF(data_shell *data_shell)
{
	char *directory;
	int success = 1;
	int spec_home, spec_delta, spec_doubdash;

	directory = data_shell->args[1];

	if (directory == NULL)
	{
		cdHomeF(data_shell);
		return (success);
	}
	spec_home = 0;
	spec_delta = 0;
	spec_doubdash = 0;
	if (cpmStrF("$HOME", directory) == spec_home ||
		cpmStrF("~", directory) == spec_delta ||
		cpmStrF("--", directory) == spec_doubdash)
	{
		cdHomeF(data_shell);
		return (success);
	}
	else
	{
		if (cpmStrF("-", directory) == 0)
		{
			cdPrevF(data_shell);

			return (success);
		}
		if (cpmStrF(".", directory) == 0 || cpmStrF("..", directory) == 0)
		{
			cdDotF(data_shell);
			return (success);
		}
		cdToDirF(data_shell);
		return (success);
	}
}

