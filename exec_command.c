#include "main.h"



/**
 * check_error_cmd - checks and handles command execution errors.
 * @direct: destination directory
 * @shell_data: data structure
 * Return: 1 on error, 0 otherwise
 */
int check_error_cmd(char *direct, data_shell *shell_data)
{
	int is_same_cmd;

	if (direct == NULL)
	{
		get_error(shell_data, 127);
		return (1);
	}

	is_same_cmd = _strcmp(shell_data->args[0], direct) == 0;

	if ((!is_same_cmd && access(direct, X_OK) == -1) || (is_same_cmd &&
				access(shell_data->args[0], X_OK) == -1))
	{
		get_error(shell_data, 126);
		free(direct);
		return (1);
	}

	free(direct);
	return (0);
}




/**
 * _which - locate the full path of an executable command (cmd)
 * in the system's environment paths
 * @inp_cmd: command input parameter
 * @_environ: the environment variable array parameter
 * Return: full path of the command, otherwise NULL.
 */
char *_which(char *inp_cmd, char **_environ)
{
	char *str_path = _getenv("PATH", _environ);
	char *tokPath, *path_copy, *direct;
	struct stat chkCmd;
	int dirLen, cmdLen;

	if (!str_path || !inp_cmd || *inp_cmd == '\0')
		return (NULL);
	if (*inp_cmd == '/')
		return ((stat(inp_cmd, &chkCmd) == 0)
				? _strdup(inp_cmd) : NULL);
	path_copy = _strdup(str_path);
	if (!path_copy)
		return (NULL);
	tokPath = _strtok(path_copy, ":");
	while (tokPath)
	{
		dirLen = _strlen(tokPath);
		cmdLen = _strlen(inp_cmd);
		direct = malloc(dirLen + cmdLen + 2);
		if (!direct)
		{
			free(path_copy);
			return (NULL);
		}
		_strcpy(direct, tokPath);
		_strcat(direct, "/");
		_strcat(direct, inp_cmd);
		if (stat(direct, &chkCmd) == 0)
		{

			free(path_copy);
			return (direct);
		}
		free(direct);
		tokPath = _strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}









/**
 * cmd_exec - executing commands provided by the user
 * @shell_data: structure parameter
 * Return: 1
 */
int cmd_exec(data_shell *shell_data)
{
	pid_t child_id;
	int chExtStat, cmd_check = is_executable(shell_data);
	char *cmd_path;

	if (cmd_check == -1)
		return (1);
	switch (cmd_check)
	{
		case 0:
			cmd_path = _which(shell_data->args[0],
					shell_data->_environ);
			if (check_error_cmd(cmd_path, shell_data) == 1)
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
			cmd_path = _which(shell_data->args[0],
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
 * is_cdir - check if the character at the current position in
 * the given path string is a colon (':').
 * @str_path: pointer to the string representing the path.
 * @cur_pos_ind: pointer to an integer representing the current
 * position in the path string.
 * Return: 1 if colon (':') was found, 0 otherwise.
 */
int is_cdir(char *str_path, int *cur_pos_ind)
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
 * is_executable - checks if input command is executable
 * checking from the data_shell structure.
 * @shell_data: structure parameter
 * Return: position from which the executable name starts, otherwise
 * 0 or -1, depending on the error value
 */
int is_executable(data_shell *shell_data)
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

	get_error(shell_data, 127);
	return (-1);
}

