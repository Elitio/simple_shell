#include "main.h"

/**
 * repeated_char - counts the repetition of a char
 *
 * @input: input string
 * @i: index
 * Return: repetitions
 */

int repeated_char(char *input, int i)
{
	if (*(input - 1) == *input)
	{
		return (repeated_char(input - 1, i + 1));
	}

	return (i);
}

/**
 * error_sep_op - Will finds syntax errors
 * @input: input string
 * @i: index
 * @last: last char read
 * Return: index of error. 0 when there are no errors
 */
int error_sep_op(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
	{
		return (0);
	}

	if (*input == ' ' || *input == '\t')
	{
		return (error_sep_op(input + 1, i + 1, last));
	}

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
		{
			return (i);
		}

	if (*input == '|')
	{
		if (last == ';' || last == '&')
		{
			return (i);
		}

		if (last == '|')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
			{
				return (i);
			}
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
		{
			return (i);
		}

		if (last == '&')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
			{
				return (i);
			}
		}
	}

	return (error_sep_op(input + 1, i + 1, *input));
}


/**
 * check_syntax_error - Finds and print a syntax error.
 *
 * @datash: a data structure.
 * @input: Input string.
 * 
 * Return: Will return 1 for error, and 0 for otherwise.
 */

int check_syntax_error( data_shell *datash, char *input)
{
	int begin = 0;
	int fir_st_char = 0;
	int i = 0;

	fir_st_char = first_char(input, &begin);
	if (fir_st_char == -1)
	{
		print_syntax_error(datash, input, begin, 0);
		return (1);
	}

	i = error_sep_op(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		print_syntax_error(datash, input, begin + i, 1);
		return (1);
	}

	return (0);
}
