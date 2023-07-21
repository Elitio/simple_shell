#include "main.h"

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


	return (0);
}
