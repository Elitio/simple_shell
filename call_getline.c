#include "holberton.h"

/**
* read_line - calls function to reads the input string.
*
* @is_end_of_file: return value of getline function
* Return: input string
*/
char *read_line(int *is_end_of_file)
{
	char *input_str = NULL;
	size_t size = 0;

	*is_end_of_file = get_line(&input_str, &size, stdin);

	return (input_str);
}
