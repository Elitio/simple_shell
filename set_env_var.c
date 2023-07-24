#include "main.h"



/**
 * _setenv - sets or updates environment variables in the shell's environment
 * @shell_data: structure parameter
 * Return: 1 on success
 */
int _setenv(data_shell *shell_data)
{
	char **input_cmds_array = shell_data->args;

	do {
		if (input_cmds_array[1] == NULL || input_cmds_array[2] == NULL)
		{
			get_error(shell_data, -1);
			return (1);
		}

		set_env(input_cmds_array[1], input_cmds_array[2], shell_data);

	} while (0);

	return (1);

}


/**
 * copy_info - creates a new string that combines these two
 *strings in the format "name=value".
 * a new env or alias
 * @env_name: name input parameter
 * @env_value: value input parameter
 * Return: the created env or alias.
 */
char *copy_info(char *env_name, char *env_value)
{
	char *final_str;
	int env_name_length = 0, env_value_length = 0;
	char *final_str_ptr;
	int final_str_length;
	char *name_ptr = env_name, *value_ptr = env_value;

	while (*name_ptr != '\0')
	{
		env_name_length++;
		name_ptr++;
	}
	while (*value_ptr != '\0')
	{
		env_value_length++;
		value_ptr++;
	}
	final_str_length = env_name_length + env_value_length + 2;
	final_str = (char *)malloc(sizeof(char) * final_str_length);
	if (final_str == NULL)
	{
		return (NULL);
	}
	final_str_ptr = final_str;
	while (*env_name != '\0')
	{
		*final_str_ptr = *env_name;
		final_str_ptr++;
		env_name++;
	}
	*final_str_ptr = '=';
	final_str_ptr++;
	while (*env_value != '\0')
	{
		*final_str_ptr = *env_value;
		final_str_ptr++;
		env_value++;
	}
	*final_str_ptr = '\0';
	return (final_str);
}



/**
 * set_env - sets or updates environment variables in the environment struct
 * @env_name: name of the environment variable to be set or updated parameter.
 * @env_value: value to be assigned to the environment variable parameter.
 * @shell_data: data structure (environ)
 * Return: nothing
 */
void set_env(char *env_name, char *env_value, data_shell *shell_data)
{
	char *check_env_var;
	int count = 0;
	char *env_name_check;
	int found_match, env_len;

	char **environ_var = shell_data->_environ;

	while (environ_var[count])
	{
		check_env_var = _strdup(environ_var[count]);
		env_name_check = _strtok(check_env_var, "=");

		found_match = (_strcmp(env_name_check, env_name) == 0);
		if (found_match)
		{
			free(environ_var[count]);
			environ_var[count] = copy_info(env_name_check,
					env_value);
			free(check_env_var);
			return;
		}

		free(check_env_var);

		count++;
	}
	env_len = count;
	environ_var = _reallocdp(environ_var, env_len, sizeof(char *)
			* (env_len + 2));
	environ_var[env_len] = copy_info(env_name, env_value);
	environ_var[env_len + 1] = NULL;
}


