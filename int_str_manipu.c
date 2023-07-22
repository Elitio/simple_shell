#include "main.h"






/**
 * aux_itoa - converts an integer to a string representation.
 * @inp_int: integer parameter
 * Return: resulting string.
 */
char *aux_itoa(int inp_int)
{
	int length = get_len(inp_int);
	char *result_str;
	unsigned int num;


	result_str = malloc(sizeof(char) * (length + 1));
	if (result_str == NULL)
		return (NULL);

	result_str[length] = '\0';

	switch (inp_int < 0)
	{
		case 1:
			num = -inp_int;
			result_str[0] = '-';
			break;
		default:
			num = inp_int;
	}

	while (length > 0)
	{
		length--;
		result_str[length] = (num % 10) + '0';
		num = num / 10;
	}

	return (result_str);
}



/**
 * _atoi - convert a string containing digits into an integer.
 * @str_wth_digs: input string parameter.
 * Return: resulting integer.
 */
int _atoi(char *str_wth_digs)
{
	int result = 0;
	int chck_sign = 1;
	int count = 0;

	if (str_wth_digs[count] == '-')
	{
		chck_sign = -1;
		count++;
	}
	while (str_wth_digs[count] >= '0' && str_wth_digs[count] <= '9')
	{
		result = result * 10 + (str_wth_digs[count] - '0');
		count++;
	}


	return (result * chck_sign);
}


/**
 * get_len - calculate the length of an integer
 * @inp_int:  int parameter
 * Return: length of integer
 */

int get_len(int inp_int)
{
	int length = 1;
	unsigned int num;


	if (inp_int < 0)
	{
		length++;
		num = (unsigned int)(-inp_int);
	}
	else
	{
		num = (unsigned int)inp_int;
	}
	while (num > 9)
	{
		length++;
		num /= 10;
	}
	return (length);
}

