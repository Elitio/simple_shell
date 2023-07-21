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
int its_executable(data_shell *datash)
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
