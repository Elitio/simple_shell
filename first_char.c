#include "main.h"

/**
 * chkChar - finds the index of first non-whitespace char of input
 * @inp_str: pointer to input string
 * @ind: pointer to int representing the index of first non-whitespace char
 * Return: -1 if its a special char, 0 if its neither a whitespace
 * character nor a special character
 */
int chkChar(char *inp_str, int *ind)
{
	*ind = 0;

	while (inp_str[*ind] && (inp_str[*ind] == ' '
				|| inp_str[*ind] == '\t'))
	{
		(*ind)++;
	}

	if (inp_str[*ind] == '\0' || inp_str[*ind] == ';' || inp_str[*ind]
			== '|' || inp_str[*ind] == '&')
	{
		return (-1);
	}

	return (0);
}
