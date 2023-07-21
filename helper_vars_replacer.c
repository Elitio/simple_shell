#include "main.h"

/**
 * is_var_empty - checks if the variable length is zero
 * @pointr: pointer parameter
 * Return: var length
 */
int is_var_empty(r_var *pointr)
{
	return (pointr->len_var == 0);
}

/**
 * is_val_empty - checks if the value length is zero
 *
 * @pointr: linked list head
 * Return: val length
 */
int is_val_empty(r_var *pointr)
{
	return (pointr->len_val == 0);
}


/**
 * copy_var_val_to_new_input - copies variable value to input string.
 *
 * @pointr: pointer to structure
 * @new_input: input parameter
 * @i: counter parameter
 * Return: variable length
 */
int copy_var_val_to_new_input(r_var *pointr, char *new_input, int i)
{
	int k = 0;

	while (k < pointr->len_val)
		new_input[i++] = pointr->val[k++];
	return (pointr->len_var);
}

/**
 * skip_var_in_input - skips the variable in the input string.
 *
 * @pointr: pointer to structure
 * Return: variable length
 */
int skip_var_in_input(r_var *pointr)
{
	int k = 0;

	while (k++ < pointr->len_var)
		continue;
	return (pointr->len_var);
}
