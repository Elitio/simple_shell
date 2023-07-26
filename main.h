#ifndef _MAIN_
#define _MAIN_


#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>


#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

extern char **environ;


/**
 * struct line_list_s - a single linked list structure
 * @line: command line variable
 * @next: next node of the list
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;


/**
 * struct sep_list_s - a singly linked list structure
 * @separator: separator
 * @next: next node of the list
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;




/**
 * struct builtin_s - Builtin structure for command arguments.
 * @name: command builtin name
 * @f: pointer func of data type
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *shell_data);
} builtin_t;

/**
 * struct r_var_list - single linked list structure
 * @len_var: variable length
 * @val: variable value
 * @len_val: value length
 * @next: next node of the list
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;


/**
 * struct data - Structure with members for keeping program variable data.
 * @input: This is the command input member.
 * @av: arguments array to the prgram.
 * @args: The command line tokens or the comand input
 * @status: The last status of the shell.
 * @counter: counter.
 * @_environ: array of environment variables
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







/*function edits */
int check_error_cmd(char *direct, data_shell *shell_data);
char *_which(char *inp_cmd, char **_environ);
int cmd_exec(data_shell *shell_data);
int is_cdir(char *str_path, int *cur_pos_ind);
int is_executable(data_shell *shell_data);
void print_syntax_error(data_shell *shell_data, char *inp_str, int ind,
		int isSingle);
int first_char(char *inp_str, int *ind);
int repeated_char(char *inp_str, int ind);
int error_sep_op(char *inp_str, int ind, char ind_sep_end);
int check_syntax_error(data_shell *shell_data, char *inp_str);
void add_nodes(sep_list **sepHead, line_list **cmdHead, char *inp_str);
char **split_line(char *inp_str);
void go_next(sep_list **sepHead, line_list **cmdHead, data_shell *shell_data);
char *swap_char(char *inp_str, int isZero);
int split_commands(data_shell *shell_data, char *inp_str);
int (*get_builtin(char *cmd))(data_shell *);





int get_value_length(char *value);
int get_command_length(char *command);
int cust_strlen(char *str_inp);
int is_var_empty(r_var *pointr);
int is_val_empty(r_var *pointr);
int copy_var_val_to_new_input(r_var *pointr, char *new_input, int i);
int skip_var_in_input(r_var *pointr);
void print_syntax_error(data_shell *datash, char *input, int i, int bool);


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

ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

char *read_line(int *is_end_of_file);

void cd_dot(data_shell *shell_data);

void cd_previous(data_shell *shell_data);

void cd_to_home(data_shell *shell_data);

void cd_to(data_shell *shell_data);

int cd_shell(data_shell *data_shell);

int _strcmp(char *first_str, char *second_str);
int _strspn(char *string, char *checkn_str);
char *_strcat(char *str_dest, const char *str_source);
char *_strchr(char *string, char charac);
char *_strcpy(char *str_dest, char *str_source);
void rev_string(char *string);
int cmp_chars(char string[], const char *delim);
char *_strtok(char string[], const char *delim);
char *_strdup(const char *string);
int _strlen(const char *string);
int _isdigit(const char *string);
char *aux_itoa(int inp_int);
int _atoi(char *str_wth_digs);
int get_len(int inp_int);
void _memcpy(void *dest_ptr, const void *src_ptr, unsigned int cpy_size);
char **_reallocdp(char **array_ptr, unsigned int prev_size,
		unsigned int realloc_size);
void *_realloc(void *inp_buffer, unsigned int prev_size,
		unsigned int realloc_size);
void free_rvar_list(r_var **head);
r_var *add_rvar_node(r_var **head, int var_len, char *var_val, int val_len);
void free_sep_list(sep_list **head);
void free_line_list(line_list **head);
sep_list *add_sep_node_end(sep_list **head, char separat);
line_list *add_line_node_end(line_list **head, char *ptr_line);
int get_error(data_shell *shell_data, int error_ref);
char *error_not_found(data_shell *shell_data);
char *error_env(data_shell *shell_data);
char *error_exit_shell(data_shell *shell_data);
char *error_path_126(data_shell *shell_data);
char *error_get_cd(data_shell *shell_data);
int exit_shell(data_shell *shell_data);
int _setenv(data_shell *shell_data);
char *copy_info(char *env_name, char *env_value);
void set_env(char *env_name, char *env_value, data_shell *shell_data);
int _unsetenv(data_shell *shell_data);
char *_getenv(const char *name_inp, char **_environ);
int _env(data_shell *shell_data);
int cmp_env_name(const char *env_var_name, const char *name_input);




#endif
