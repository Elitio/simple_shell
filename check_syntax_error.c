#include "main.h"


/**
 * check_syntax_error - intermediate function to
 * find and print a syntax error
 * @shell_data: structure
 * @inp_str: input string
 * Return: 1 if there is an error. 0 in other case
 */
int check_syntax_error(data_shell *shell_data, char *inp_str)
{
	int start_ind = 0, err_ind;
	int reslt = first_char(inp_str, &start_ind);

	do {
		if (reslt == -1)
		{
			print_syntax_error(shell_data, inp_str, start_ind, 0);
			return (1);
		}

		err_ind = error_sep_op(inp_str + start_ind, 0,
				inp_str[start_ind]);
		if (err_ind != 0)
		{
			print_syntax_error(shell_data, inp_str, start_ind
					+ err_ind, 1);
			return (1);
		}

	} while (0);

	return (0);
}



/**
 * repeated_char - counts the number of repeated occurrences of a character
 * in a string, starting from a given position.
 * @inp_str: input string
 * @ind: current count of repeated occurrences.
 * Return: current count ind if characters are not equal
 */
int repeated_char(char *inp_str, int ind)
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
 * error_sep_op - finds syntax errors
 *
 * @inp_str: input command line string.
 * @ind: index of the current character in the input string
 * @ind_sep_end: last separator character encountered before the current index.
 * Return: 0 on no syntax errors related to separators.
 */
int error_sep_op(char *inp_str, int ind, char ind_sep_end)
{
	int count;

	if (*inp_str == '\0')
		return (0);

	if (*inp_str == ' ' || *inp_str == '\t')
		return (error_sep_op(inp_str + 1, ind + 1, ind_sep_end));

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
				count = repeated_char(inp_str, 0);
				if (count == 0 || count > 1)
					return (ind);
			}
			break;
	}

	return (error_sep_op(inp_str + 1, ind + 1, *inp_str));
}

