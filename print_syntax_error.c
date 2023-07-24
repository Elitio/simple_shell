#include "main.h"

/**
 * print_syntax_error - prints when a syntax error is found
 * @datash: data structure
 * @input: input string
 * @i: index of the error
 * @bool: to control message errors
 * Return: no return
 */
void print_syntax_error(data_shell *datash, char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = aux_itoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	strcpy(error, datash->av[0]);
	strcat(error, ": ");
	strcat(error, counter);
	strcat(error, msg2);
	strcat(error, msg);
	strcat(error, msg3);
	strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}