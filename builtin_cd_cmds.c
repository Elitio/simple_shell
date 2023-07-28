#include "main.h"


/**
 * cd_dot - handles the cd command with the argument "."
 *
 * @shell_data: structure parameter
 * Return: no return
 */
void cd_dot(data_shell *shell_data)
{
	char *directory, *copied_current_dir, current_dir[PATH_MAX], *tok_dir;

	getcwd(current_dir, sizeof(current_dir));
	copied_current_dir = _strdup(current_dir);
	set_env("OLDPWD", copied_current_dir, shell_data);
	directory = shell_data->args[1];
	switch (_strcmp(".", directory))
	{
		case 0:
			set_env("PWD", copied_current_dir, shell_data);
			free(copied_current_dir);
			return;
		default:
			break;
	}
	switch (_strcmp("/", copied_current_dir))
	{
		case 0:
			free(copied_current_dir);
			return;
		default:
			break;
	}
	tok_dir = copied_current_dir;
	rev_string(tok_dir);
	tok_dir = _strtok(tok_dir, "/");
	if (tok_dir != NULL)
		tok_dir = _strtok(NULL, "\0");
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
 * cd_previous - changes directory from the current one to the previous one
 *
 * @shell_data: structure parameter
 * Return: nothing
 */
void cd_previous(data_shell *shell_data)
{
	char *new_current_dir, *prev_dir, current_dir[PATH_MAX];
	char *copied_current_dir;
	char *copied_prev_dir;

	getcwd(current_dir, sizeof(current_dir));
	copied_current_dir = _strdup(current_dir);

	prev_dir = _getenv("OLDPWD", shell_data->_environ);

	switch (prev_dir != NULL)
	{
		case 0:
			copied_prev_dir = copied_current_dir;
			break;
		case 1:
			copied_prev_dir = _strdup(prev_dir);
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
	write(STDOUT_FILENO, new_current_dir, _strlen(new_current_dir));
	write(STDOUT_FILENO, "\n", 1);
	free(copied_current_dir);
	if (prev_dir)
		free(copied_prev_dir);
	shell_data->status = 0;
}













/**
 * cd_to_home - changes directory from the current one to home directory
 *
 * @shell_data: structure parameter
 * Return: nothing
 */
void cd_to_home(data_shell *shell_data)
{
	char *copied_current_dir, current_dir[PATH_MAX], *home_dir;

	getcwd(current_dir, sizeof(current_dir));

	copied_current_dir = _strdup(current_dir);

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
			get_error(shell_data, 2);
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
 * cd_to - changes directory from the current one to the one specified
 *
 * @shell_data: structure parameter
 * Return: nothing
 */
void cd_to(data_shell *shell_data)
{
	char *directory, *copied_current_dir, current_dir[PATH_MAX];
	char *copied_spec_dir;

	getcwd(current_dir, sizeof(current_dir));

	directory = shell_data->args[1];

	if (chdir(directory) == -1)
	{
		get_error(shell_data, 2);

		return;
	}

	copied_current_dir = _strdup(current_dir);
	copied_spec_dir = _strdup(directory);

	set_env("OLDPWD", copied_current_dir, shell_data);

	set_env("PWD", copied_spec_dir, shell_data);

	free(copied_current_dir);

	free(copied_spec_dir);

	shell_data->status = 0;
}




/**
 * cd_shell - handles the cd command with or without args
 *
 * @data_shell: structure parameter
 * Return: 1 on success
 */
int cd_shell(data_shell *data_shell)
{
	char *directory;
	int success = 1;
	int spec_home, spec_delta, spec_doubdash;

	directory = data_shell->args[1];

	if (directory == NULL)
	{
		cd_to_home(data_shell);
		return (success);
	}
	spec_home = 0;
	spec_delta = 0;
	spec_doubdash = 0;
	if (_strcmp("$HOME", directory) == spec_home ||
		_strcmp("~", directory) == spec_delta ||
		_strcmp("--", directory) == spec_doubdash)
	{
		cd_to_home(data_shell);
		return (success);
	}
	else
	{
		if (_strcmp("-", directory) == 0)
		{
			cd_previous(data_shell);

			return (success);
		}
		if (_strcmp(".", directory) == 0 || _strcmp("..", directory) == 0)
		{
			cd_dot(data_shell);
			return (success);
		}
		cd_to(data_shell);
		return (success);
	}
}

