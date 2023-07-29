#include "main.h"

/**
 * getSigF - Handles crtl + c signals.
 * @signal: Signal parameter
 */
void getSigF(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n$ ", 3);
}
