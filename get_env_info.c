#include "main.h"


/**
 * _getenv - retrieve the value of an environment variable given its name.
 * @name_inp: name of the environment variable to be searched for.
 * @_environ:  array of strings representing the environment variables.
 * Return: pointer to the value of the matched environment variable
 * Otherwise NULL.
 */
char *_getenv(const char *name_inp, char **_environ)
{
	char *matched_var;
	int equal_ind = 0;
	int env_ind = 0;

	while (_environ[env_ind])
	{
		equal_ind = cmpEnvNameF(_environ[env_ind], name_inp);
		if (equal_ind)
		{
			matched_var = _environ[env_ind] + equal_ind;
			return (matched_var);
		}
		env_ind++;
	}

	return (NULL);
}





/**
 * _env - print the current environment variables to standard output
 * @shell_data: structure parameter
 * Return: 1 for successful operation.
 */
int _env(data_shell *shell_data)
{
	int count1 = 0;
	int count2;

	while (shell_data->_environ[count1])
	{
		count2 = 0;
		while (shell_data->_environ[count1][count2])
			count2++;

		write(STDOUT_FILENO, shell_data->_environ[count1], count2);
		write(STDOUT_FILENO, "\n", 1);

		count1++;
	}

	shell_data->status = 0;
	return (1);
}

/**
 * cmpEnvNameF - compare an environment variable's name with name input
 * @env_var_name: the environment variable
 * @name_input: the name to compare with
 * Return: 0 if they are not equal or i + 1
 */
int cmpEnvNameF(const char *env_var_name, const char *name_input)
{
	int i = 0;

	while (env_var_name[i] && env_var_name[i] != '=' && env_var_name[i]
			== name_input[i])
	{
		i++;
	}

	return (env_var_name[i] == '=' ? i + 1 : 0);
}

