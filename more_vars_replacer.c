#include "holberton.h"

/**
 * get_value_length - Finds value length
 * @value: parameter
 * Return: length
 **/
int get_value_length(char *value)
{
	int length = 0;

	while (value[length] != '\0')
		length++;
	return (length);
}


/**
 * get_command_length - Find length of command
 * @command: parameter
 * Return: length
 */
int get_command_length(char *command)
{
	int length = 0;

	while (command[length] != ' ' && command[length] != '\t' &&
			command[length] != ';' && command[length] != '\n'
			&& command[length] != '\0')
	{
		length++;
	}
	return (length);
}
