#include "main.h"

/**
* callGetLineF - calls function to reads the input string.
*
* @is_end_of_file: return value of getline function
* Return: input string
*/
char *callGetLineF(int *is_end_of_file)
{
	/* Declare variables to store the input string and its size */
	char *input_str = NULL;
	size_t size = 0;

	/* Call the function getLineF to read the input from
	 * the user via stdin (standard input)
	 * */
	*is_end_of_file = getLineF(&input_str, &size, stdin);

	/* Return the input string read from the user */
	return (input_str);
}
