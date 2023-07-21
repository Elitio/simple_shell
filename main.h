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
 * struct data - Structure with members for keeping program variable data.
 * @input: This is the command input member.
 * @av: argument array.
 * @args: Thew command line tokens
 * @status: The last status of the shell.
 * @counter: lines counter.
 * @_environ: environment variable.
 * @pid: Process ID
 */

typedef struct data
{
	char *input;
	char **av;
	char args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

char *swap_char(char *input, int option);
char *without_comment(char *in);
int first_char(char *input, int *i);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash);
int split_commands(data_shell *datash, char *input);
char **split_line(char *input);
int is_cdir(char *path_str, int *index_ptr);
char *which(char *cmd, char **environ);
int its_executable(data_shell *datash);

/* new functions added */
int get_value_length(char *value);
int get_command_length(char *command);
int cust_strlen(char *str_inp);
int is_var_empty(r_var *pointr);
int is_val_empty(r_var *pointr);
int copy_var_val_to_new_input(r_var *pointr, char *new_input, int i);
int skip_var_in_input(r_var *pointr);



/*old functions added */
void check_env(r_var **strnode, char *user_inp, data_shell *struct_info);

int check_vars(r_var **strnode, char *user_inp, char *str_stat,
		data_shell *struct_info);

void set_data(data_shell *shell_data, char **arg_vector);

void free_data(data_shell *shell_data);
char *without_comment(char *input_str);

void shell_loop(data_shell *data_shell_info);

void get_sigint(int signal);

char *replaced_input(r_var **strNode, char *str_inp, char *replaced_str,
int len_new);

char *rep_var(char *str_inp, data_shell *struct_info);



#endif
