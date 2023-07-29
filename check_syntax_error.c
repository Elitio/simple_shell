#include "main.h"


/**
 * chkInEror - intermediate function to
 * find and print a syntax error
 * @shell_data: structure
 * @inp_str: input string
 * Return: 1 if there is an error. 0 in other case
 */
int chkInEror(data_shell *shell_data, char *inp_str)
{
	int start_ind = 0, err_ind;
	int reslt = chkChar(inp_str, &start_ind);

	do {
		if (reslt == -1)
		{
			printInError(shell_data, inp_str, start_ind, 0);
			return (1);
		}

		err_ind = sepError(inp_str + start_ind, 0,
				inp_str[start_ind]);
		if (err_ind != 0)
		{
			printInError(shell_data, inp_str, start_ind
					+ err_ind, 1);
			return (1);
		}

	} while (0);

	return (0);
}



/**
 * repChar - counts the number of repeated occurrences of a character
 * in a string, starting from a given position.
 * @inp_str: input string
 * @ind: current count of repeated occurrences.
 * Return: current count ind if characters are not equal
 */
int repChar(char *inp_str, int ind)
{
	int count = 0;

	while (*(inp_str + ind) == *(inp_str + ind - 1))
	{
		count++;

		ind++;
	}

	return (count);
}





/**
 * sepError - finds syntax errors
 *
 * @inp_str: input command line string.
 * @ind: index of the current character in the input string
 * @ind_sep_end: last separator character encountered before the current index.
 * Return: 0 on no syntax errors related to separators.
 */
int sepError(char *inp_str, int ind, char ind_sep_end)
{
	int count;

	if (*inp_str == '\0')
		return (0);

	if (*inp_str == ' ' || *inp_str == '\t')
		return (sepError(inp_str + 1, ind + 1, ind_sep_end));

	switch (*inp_str)
	{
		case ';':
			if (ind_sep_end == '|' || ind_sep_end == '&'
					|| ind_sep_end == ';')
				return (ind);
			break;
		case '|':
		case '&':
			if (ind_sep_end == ';' || ind_sep_end == '|')
			{
				count = repChar(inp_str, 0);
				if (count == 0 || count > 1)
					return (ind);
			}
			break;
	}

	return (sepError(inp_str + 1, ind + 1, *inp_str));
}

