#include "main.h"

/**
 * get_sigint - Handles crtl + c signals.
 * @signal: Signal parameter
 */
void get_sigint(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n$ ", 3);
}
