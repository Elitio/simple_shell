#include "main.h"

/**
* callGetLineF - calls function to reads the input string.
*
* @is_end_of_file: return value of getline function
* Return: input string
*/
char *callGetLineF(int *is_end_of_file)
{
	char *input_str = NULL;
	size_t size = 0;

	*is_end_of_file = getLineF(&input_str, &size, stdin);

	return (input_str);
}
