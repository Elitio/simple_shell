#include "main.h"

/**
 * check_env - checks if the typed variable is an env variable
 *
 * @strnode: linked list head
 * @user_inp: input parameter
 * @struct_info: data structure
 * Return: no return
 */
void check_env(r_var **strnode, char *user_inp, data_shell *struct_info)
{
	int horizon = 0, vert;
	char **env_var;
	char nul_term = '\0', equal = '=';
	int cmd_length = 1, val_length;

	env_var = struct_info->_environ;

	while (env_var[horizon] != NULL)
	{
		vert = 0;

		while (env_var[horizon][vert] != nul_term)
		{
			if (env_var[horizon][vert] == equal)
			{
				val_length = get_value_length(env_var[horizon]
				+ vert + 1);
				add_rvar_node(strnode, cmd_length,
				env_var[horizon] + vert + 1,
				val_length);
				return;
			}
			if (user_inp[cmd_length] == env_var[horizon][vert])
				cmd_length++;

			else
				break;

			vert++;
		}
		horizon++;
	}

	cmd_length = get_command_length(user_inp);

	add_rvar_node(strnode, cmd_length, NULL, 0);
}



/**
 * check_vars - check if the typed variable is $$ or $?
 *
 * @strnode: head of the linked list
 * @user_inp: input parameter
 * @str_stat: last status parameter
 * @struct_info: defined data structure parameter
 * Return: nothing
 */
int check_vars(r_var **strnode, char *user_inp, char *str_stat,
		data_shell *struct_info)
{
	int counter = 0;
	char nxtChar = user_inp[counter + 1];
	char nul_term = '\0', dollar = '$';
	int str_length = cust_strlen(str_stat);
	int pid_length = cust_strlen(struct_info->pid);

	while (user_inp[counter] != nul_term)
	{
		if (user_inp[counter] == dollar)
	{

		switch (nxtChar)
		{
			case '$':
				add_rvar_node(strnode, 2, struct_info->pid,
				pid_length);
				counter++;
				break;

			case '?':
				add_rvar_node(strnode, 2, str_stat, str_length);
				counter++;
				break;

			case '\n': case ' ': case '\0': case ';': case '\t':
				add_rvar_node(strnode, 0, NULL, 0);
				break;

			default:
				check_env(strnode, user_inp + counter,
				struct_info);
				break;
		}
	}

		counter++;
	}

	return (counter);
}

/**
 * cust_strlen - finds the length of a string
 * @str_inp: input string parameter
 * Return: string length
 */
int cust_strlen(char *str_inp)
{
	int length = 0;
	char nul_term = '\0';

	while (str_inp[length] != nul_term)
	{
		length++;
	}
	return (length);
}

/**
 * replaced_input - replaces string into variables
 *
 * @strNode: head of the linked list
 * @str_inp: input string parameter
 * @replaced_str: replaced input string parameter
 * @len_new: new length parameter
 * Return: the replaced string.
 */
char *replaced_input(r_var **strNode, char *str_inp, char *replaced_str,
int len_new)
{
	int i = 0, j = 0;
	r_var *pointr = *strNode;

	while (i < len_new)
	{
		if (str_inp[j] == '$')
		{
			if (is_var_empty(pointr))
			{
				if (is_val_empty(pointr))
					replaced_str[i] = str_inp[j++];
				else
				{
					j += copy_var_val_to_new_input(pointr,
					replaced_str, i);
					i--;
				}
			}
			else
			{
				if (is_val_empty(pointr))
				{
					j += skip_var_in_input(pointr);
					i--;
				}
				else
				{
					j += copy_var_val_to_new_input(pointr,
					replaced_str, i);
					i--;
				}
			}
			pointr = pointr->next;
		}
		else
			replaced_str[i] = str_inp[j++];
		i++;
	}
	return (replaced_str);
}


/**
 * rep_var - performs variable replacement in the input string using a linked
 * list of variables stored in the head structure
 *
 * @str_inp: input string parameter
 * @struct_info: structure parameter
 * Return: replaced string
 */
char *rep_var(char *str_inp, data_shell *struct_info)
{
	char *str_stat;
	char *replaced_str;
	r_var *strNode = NULL, *pointr;
	int orig_len;

	int len_new;

	str_stat = aux_itoa(struct_info->status);
	orig_len = check_vars(&strNode, str_inp, str_stat, struct_info);

	if (strNode == NULL)
	{
		free(str_stat);
		return (str_inp);
	}
	len_new = 0;
	for (pointr = strNode; pointr != NULL; pointr = pointr->next)
	{
		len_new += (pointr->len_val - pointr->len_var);
	}
	len_new += orig_len;


	replaced_str = malloc(sizeof(char) * (len_new + 1));

	replaced_str[len_new] = '\0';
	replaced_str = replaced_input(&strNode, str_inp, replaced_str,
			len_new);

	free(str_inp);

	free(str_stat);

	free_rvar_list(&strNode);
	return (replaced_str);
}
