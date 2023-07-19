#ifndef _MAIN_
#define _MAIN_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;

/**
 * struct data - Contains all important data for runtime purposes.
 * @input: This is the command line written by a user.
 * @av: argument vector.
 * @args: The tokens of the the command line.
 * @status: The last status of the shell.
 * @counter: The lines counter.
 * @_environ: The environment variable.
 * @pid: Process ID of the shell.
 */

typedef struct data
{
	char *input;
	char **av;
	char args;
	int status;
	int counter;
	char **_envirion;
	char *pid;
} data_shell;

char *custom_swap(char *input, int option);
char *without_comment(char *in);
int first_char(char *input, int *i);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash);
int split_commands(data_shell *datash, char *input);
char **split_line(char *input);
#endif
