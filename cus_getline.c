#include "main.h"

/**
* init_buffer - initiate buffer and size of buffer allocate memory for it
* @lineptr: buffer that stores the input
* @n: size of buffer
* Return: 0 on success or -1 otherwise
*/
static int init_buffer(char **lineptr, size_t *n)
{
	if (!*lineptr || !*n)
	{
		*n = 128;
		*lineptr = (char *) malloc(*n);
		if (!*lineptr)
		{
			return (-1);
		}
	}
	return (0);
}

/**
 * expand_buffer- reallocates more memory blocks by doubling buffer size
 * @lineptr: Buffer that store the input string
 * @n: size of buffer
 * @i: number of chars read
 * Return: 0 on success or -1 otherwise
 */
static int expand_buffer(char **lineptr, size_t *n, ssize_t i)
{
	char *new_ptr;
	ssize_t j;

	if ((size_t)i >= (*n - 1))
	{
		*n *= 2;
		new_ptr = (char *) malloc(*n);

		if (!new_ptr)
		{

			return (-1);
		}
		for (j = 0; j < i; j++)
		{
			new_ptr[j] = (*lineptr)[j];
		}
		free(*lineptr);
		*lineptr = new_ptr;
	}
	return (0);
}

/**
* read_char - reads a single character from the input stream and stores it
* @c: A pointer to a char variable where the read character will be stored.
* @stream: The input stream from which the character will be read
* Return: 1 on success or -1 otherwise
*/
static ssize_t read_char(char *c, FILE *stream)
{
	if (read(fileno(stream), c, 1) == 1)
	{
		return (1);
	}
	else
	{
		return (-1);
	}
}


/**
* get_line -  reads input line from the stream and store it in the buffer
* @lineptr: A pointer to a pointer that will store the address of the buffer
* @n: A pointer to the size of the buffer
* @stream: The input stream from which the character will be read
* Return: the number of characters or -1 on error
*/
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t i = 0;
	char c;

	if (init_buffer(lineptr, n) < 0)
	{
		return (-1);
	}

	while (read_char(&c, stream) > 0)
	{
		if (expand_buffer(lineptr, n, i) < 0)
		{
			return (-1);
		}
		(*lineptr)[i++] = c;

		if (c == '\n')
		{

			break;
		}
	}

	(*lineptr)[i] = '\0';
	if (i == 0)
	{
		return (-1);
	}

	return (i);
}
