#include "main.h"


/**
 * _memcpy - it copies bytes from a source memory area to a dest memory area
 * @dest_ptr: destination pointer parameter
 * @src_ptr: source pointer parameter
 * @cpy_size: size of new pointer.
 * Return: nothing
 */
void _memcpy(void *dest_ptr, const void *src_ptr, unsigned int cpy_size)
{

	char *src_char_ptr = (char *)src_ptr;
	unsigned int count = 0;
	char *dest_char_ptr = (char *)dest_ptr;


	while (count < cpy_size)
	{
		dest_char_ptr[count] = src_char_ptr[count];
		count++;
	}
}
