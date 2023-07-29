#include "main.h"



/**
 * reallocDpF -  reallocate memory for a dynamic array of strings.
 * @array_ptr: Pointer to the existing dynamic array of strings.
 * @prev_size: current size of the dynamic array (number of elements).
 * @realloc_size: desired new size of the dynamic array (number of elements).
 * Return: pointer to the newly allocated memory (newptr) after the
 * reallocation or NULL on failure.
 */
char **reallocDpF(char **array_ptr, unsigned int prev_size,
		unsigned int realloc_size)
{
	unsigned int count = 0;

	char **new_ptr;

	if (array_ptr == NULL)
		return (malloc(sizeof(char *) * realloc_size));
	if (realloc_size == prev_size)
		return (array_ptr);

	new_ptr = malloc(sizeof(char *) * realloc_size);

	if (new_ptr == NULL)
		return (NULL);
	do {
		if (count < prev_size && count < realloc_size)
			new_ptr[count] = array_ptr[count];
		count++;
	} while (count < realloc_size);


	free(array_ptr);
	return (new_ptr);

}



/**
 * reallocFnc - reallocates memory for a previously allocated memory block.
 * @inp_buffer: memory previously allocated.
 * @prev_size: previously allocated memory size.
 * @realloc_size: newly allocated memory size.
 * Return: reallocated buffer, previous buffer or NULL
 */
void *reallocFnc(void *inp_buffer, unsigned int prev_size,
		unsigned int realloc_size)
{
	unsigned int cpy_size;
	unsigned char *dest_char_ptr;
	unsigned char *src_char_ptr;
	void *new_ptr;
	unsigned int count;


	if (realloc_size == 0)
	{
		free(inp_buffer);
		return (NULL);
	}
	if (inp_buffer == NULL)
		return (malloc(realloc_size));
	if (realloc_size == prev_size)
		return (inp_buffer);
	new_ptr = malloc(realloc_size);

	if (new_ptr == NULL)
		return (NULL);

	cpy_size = (realloc_size < prev_size) ? realloc_size : prev_size;

	dest_char_ptr = (unsigned char *)new_ptr;
	src_char_ptr = (unsigned char *)inp_buffer;

	count = 0;
	while (count < cpy_size)
	{
		dest_char_ptr[count] = src_char_ptr[count];
		count++;
	}

	free(inp_buffer);

	return (new_ptr);
}


