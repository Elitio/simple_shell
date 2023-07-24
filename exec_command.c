#include "main.h"

/**
 * is_cdir - Will checks if ":" is in the current directory.
 * @path_str: Pointer to a character array representing the path.
 * @index_ptr: Pointer to an integer representing the index to check.
 * Return: 1 if the path is searchable in the current directory, 0 otherwise.
 */

int is_cdir(char *path_str, int *index_ptr)
{
	if (path_str[*index_ptr] == ':')
	{
		return 1;
	}

	while (path_str[*index_ptr] != ':' && path_str[*index_ptr])
	{
		(*index_ptr)++;
	}

	if (path_str[*index_ptr])
	{
		(*index_ptr)++;
	}

	return (0);
}

/**
 * which - function pointer to locate a command.
 *
 * @cmd: command name
 * @environ: pointer to the pointer of the environment variable
 * Return: location of the command.
 */

char *which(char *cmd, char **environ)
{
    char *path, *ptr_path, *token_path, *dir;
    int len_dir, len_cmd, i;
    struct stat st;

    path = getenv("PATH", environ);
    if (path)
    {
        ptr_path = strdup(path);
        len_cmd = strlen(cmd);
        token_path = strtok(ptr_path, ":");
        i = 0;
        while (token_path != NULL)
        {
            if (is_cdir(path, &i))
                if (stat(cmd, &st) == 0)
                    return cmd;
            len_dir = strlen(token_path);
            dir = malloc(len_dir + len_cmd + 2);
            strcpy(dir, token_path);
            strcat(dir, "/");
            strcat(dir, cmd);
            strcat(dir, "\0");
            if (stat(dir, &st) == 0)
            {
                free(ptr_path);
                return dir;
            }
            free(dir);
            token_path = strtok(NULL, ":");
        }
        free(ptr_path);
        if (stat(cmd, &st) == 0)
            return cmd;
        return NULL;
    }
    if (cmd[0] == '/')
        if (stat(cmd, &st) == 0)
            return cmd;
    return NULL;
}


/**
 * is_executable - determines if is an executable
 *
 * @datash: data structure
 * Return: 0 if it is not an executable, the index if it is.
 */
int is_executable(data_shell *datash)
{
	struct stat st;
	int i = 0;
	char *input = datash->args[0];

	while (input[i])
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.' || input[i + 1] == '/')
			{
				return (0);
			}
			else
			{
				break;
			}
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
			{
				i++;
				continue;
			}
			break;
		}
		else
			break;
		i++;
	}

	if (i == 0)
	{
		return (0);
	}

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}

	get_error(datash, 127);
	return (-1);
}

/**
 * check_error_cmd - verifies if user has permissions to access.
 *
 * @dir: destination directory
 * @datash: data structure
 * Return: 1 if there is an error, 0 if not
 */

int check_error_cmd(char *dir, data_shell *datash)
{
	int is_error = 0;

	if (dir == NULL)
	{
		get_error(datash, 127);
		is_error = 1;
	}
	else if (strcmp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(datash, 126);
			is_error = 1;
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			get_error(datash, 126);
			is_error = 1;
		}
	}
       
	return is_error;
}

/**
 * execute_command - executes command lines args.
 *
 * @datash: relevant accessed data are args and inpu.
 * Return: 1 on success.
 */

int execute_command(data_shell *datash)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = is_executable(datash);
	if (exec == -1)
	{
		return (1);
	}
	if (exec == 0)
	{
		dir = which(datash->args[0], datash->_environ);
		if (check_error_cmd(dir, datash) == 1)
		{
			return (1);
		}
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
		{
			dir = which(datash->args[0], datash->_environ);
		}
        else
	{
		dir = datash->args[0];
		execve(dir + exec, datash->args, datash->_environ);
	}
	else if (pd < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do
		{
			wpd = waitpid(pd, &state, WUNTRACED);
		}
		while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	datash->status = state / 256;
	return (1);
}
