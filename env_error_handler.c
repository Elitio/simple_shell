#include "main.h"

/**
 * envErrorF - generates an error message with details about program name and
 * program version
 * @shell_data: structure parameter
 * Return: error message
 */
char *envErrorF(data_shell *shell_data)
{
	char *env_er_str = intToStrF(shell_data->counter);
	int buff_len;
	char *envErrorF_msg = ": Failure handling the environment";
	char *err_str, *err_ptr, *av0_ptr = shell_data->av[0];

	buff_len = lenStrF(shell_data->av[0]) + lenStrF(env_er_str)
		+ lenStrF(shell_data->args[0]) + lenStrF(envErrorF_msg) + 4;
	err_str = malloc(sizeof(char) * (buff_len + 1));
	if (err_str == NULL)
	{
		free(env_er_str);
		return (NULL);
	}
	err_ptr = err_str;
	while (*av0_ptr != '\0')
	{
		*err_ptr = *av0_ptr;
		av0_ptr++;
		err_ptr++;
	}
	*err_ptr++ = ':';
	*err_ptr++ = ' ';
	while (*env_er_str != '\0')
	{
		*err_ptr = *env_er_str;
		env_er_str++;
		err_ptr++;
	}
	*err_ptr++ = ':';
	*err_ptr++ = ' ';
	while (*envErrorF_msg != '\0')
	{
		*err_ptr = *envErrorF_msg;
		envErrorF_msg++;
		err_ptr++;
	}
	*err_ptr = '\0';
	free(env_er_str);
	return (err_str);
}

