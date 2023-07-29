#include "main.h"



/**
 * command_err - checks and handles command execution errors.
 * @direct: destination directory
 * @shell_data: data structure
 * Return: 1 on error, 0 otherwise
 */
int command_err(char *direct, data_shell *shell_data)
{
	int is_same_cmd;

	if (direct == NULL)
	{
		getErrorF(shell_data, 127);
		return (1);
	}

	is_same_cmd = cpmStrF(shell_data->args[0], direct) == 0;

	if ((!is_same_cmd && access(direct, X_OK) == -1) || (is_same_cmd &&
				access(shell_data->args[0], X_OK) == -1))
	{
		getErrorF(shell_data, 126);
		free(direct);
		return (1);
	}

	free(direct);
	return (0);
}




/**
 * find_pth - locate the full path of an executable command (cmd)
 * in the system's environment paths
 * @inp_cmd: command input parameter
 * @_environ: the environment variable array parameter
 * Return: full path of the command, otherwise NULL.
 */
char *find_pth(char *inp_cmd, char **_environ)
{
	char *str_path = _getenv("PATH", _environ);
	char *tokPath, *path_copy, *direct;
	struct stat chkCmd;
	int dirLen, cmdLen;

	if (!str_path || !inp_cmd || *inp_cmd == '\0')
		return (NULL);
	if (*inp_cmd == '/')
		return ((stat(inp_cmd, &chkCmd) == 0)
				? dupStrF(inp_cmd) : NULL);
	path_copy = dupStrF(str_path);
	if (!path_copy)
		return (NULL);
	tokPath = tokStrF(path_copy, ":");
	while (tokPath)
	{
		dirLen = lenStrF(tokPath);
		cmdLen = lenStrF(inp_cmd);
		direct = malloc(dirLen + cmdLen + 2);
		if (!direct)
		{
			free(path_copy);
			return (NULL);
		}
		cpyStrF(direct, tokPath);
		catStrF(direct, "/");
		catStrF(direct, inp_cmd);
		if (stat(direct, &chkCmd) == 0)
		{

			free(path_copy);
			return (direct);
		}
		free(direct);
		tokPath = tokStrF(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}









/**
 * _execute - executing commands provided by the user
 * @shell_data: structure parameter
 * Return: 1
 */
int _execute(data_shell *shell_data)
{
	pid_t child_id;
	int chExtStat, cmd_check = can_exec(shell_data);
	char *cmd_path;

	if (cmd_check == -1)
		return (1);
	switch (cmd_check)
	{
		case 0:
			cmd_path = find_pth(shell_data->args[0],
					shell_data->_environ);
			if (command_err(cmd_path, shell_data) == 1)
				return (1);
			break;
		default:
			cmd_path = shell_data->args[0];
			break;
	}
	child_id = fork();
	if (child_id == 0)
	{
		if (cmd_check == 0)
			cmd_path = find_pth(shell_data->args[0],
					shell_data->_environ);
		else
			cmd_path = shell_data->args[0];
		execve(cmd_path + cmd_check, shell_data->args,
				shell_data->_environ);
	}
	else if (child_id < 0)
	{
		perror(shell_data->av[0]);
		return (1);
	}
	else
	{
		waitpid(child_id, &chExtStat, WUNTRACED);
	}
	shell_data->status = WIFEXITED(chExtStat) ? WEXITSTATUS(chExtStat) : 1;
	return (1);
}










/**
 * chk_dir - check if the character at the current position in
 * the given path string is a colon (':').
 * @str_path: pointer to the string representing the path.
 * @cur_pos_ind: pointer to an integer representing the current
 * position in the path string.
 * Return: 1 if colon (':') was found, 0 otherwise.
 */
int chk_dir(char *str_path, int *cur_pos_ind)
{
	if (str_path[*cur_pos_ind] == ':')
	{
		(*cur_pos_ind)++;
		return (1);
	}

	for (; str_path[*cur_pos_ind] && str_path[*cur_pos_ind]
			!= ':'; (*cur_pos_ind)++)
		;

	if (str_path[*cur_pos_ind] == ':')
	{
		(*cur_pos_ind)++;
	}

	return (0);
}








/**
 * can_exec - checks if input command is executable
 * checking from the data_shell structure.
 * @shell_data: structure parameter
 * Return: position from which the executable name starts, otherwise
 * 0 or -1, depending on the error value
 */
int can_exec(data_shell *shell_data)
{
	char *cmd_inp = shell_data->args[0];

	int cmd_ind = 0;

	struct stat chkCmd;

	while (cmd_inp[cmd_ind] == '.' || cmd_inp[cmd_ind] == '/')
	{
		if (cmd_inp[cmd_ind] == '.')
		{
			if (cmd_inp[cmd_ind + 1] == '.' ||
					cmd_inp[cmd_ind + 1] == '/')
				return (0);
		}
		else
		{
			if (cmd_ind == 0)
				return (0);
			if (cmd_inp[cmd_ind + 1] == '.')
				return (0);
		}

		cmd_ind++;
	}

	if (cmd_ind == 0)
		return (0);

	if (stat(cmd_inp + cmd_ind, &chkCmd) == 0)
		return (cmd_ind);

	getErrorF(shell_data, 127);
	return (-1);
}

