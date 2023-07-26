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




#define TOK_DELIM " \t\r\n\a"

#define BUFSIZE 1024






#define TOK_BUFSIZE 128





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
	int (*f)(data_shell *datash);
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
	char **args;
	int status;
	char **av;
	int counter;
	char **_environ;
	char *pid;
} data_shell;




/* new functions added */
int get_value_length(char *value);
int get_command_length(char *command);
int cust_strlen(char *str_inp);
int is_var_empty(r_var *pointr);
int is_val_empty(r_var *pointr);
int copy_var_val_to_new_input(r_var *pointr, char *new_input, int i);
int skip_var_in_input(r_var *pointr);
void set_data(data_shell *shell_data, char **arg_vector);
void free_data(data_shell *shell_data);







/*void cleanup_resources(char *str_inp, char *str_stat, r_var **strNode);*/

/* aux_lists.c */
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* aux_lists2.c */
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

/* aux_str functions */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* aux_mem.c */
void _memcpy(void *dest_ptr, const void *src_ptr, unsigned int cpy_size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* aux_str2.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* aux_str3.c */
void rev_string(char *s);

/* check_syntax_error.c */
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(data_shell *datash, char *input, int i, int bool);
int check_syntax_error(data_shell *datash, char *input);

/* shell_loop.c */
char *without_comment(char *input_str);
void shell_loop(data_shell *data_shell_info);

/* read_line.c */
char *read_line(int *i_eof);

/* split.c */
char *swap_char(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash);
int split_commands(data_shell *datash, char *input);
char **split_line(char *input);

/* rep_var.c */
void check_env(r_var **strnode, char *user_inp, data_shell *struct_info);
int check_vars(r_var **strnode, char *user_inp, char *str_stat,
		data_shell *struct_info);
char *replaced_input(r_var **strNode, char *str_inp, char *replaced_str,
int len_new);
char *rep_var(char *str_inp, data_shell *struct_info);

/* get_line.c */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* exec_line */
int exec_line(data_shell *datash);

/* cmd_exec.c */
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(data_shell *datash);
int check_error_cmd(char *dir, data_shell *datash);
int cmd_exec(data_shell *datash);

/* env1.c */
char *_getenv(const char *name, char **_environ);
int _env(data_shell *datash);
int cmp_env_name(const char *nenv, const char *name);

/* env2.c */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, data_shell *datash);
int _setenv(data_shell *datash);
int _unsetenv(data_shell *datash);

/* cd.c */
void cd_dot(data_shell *datash);
void cd_to(data_shell *datash);
void cd_previous(data_shell *datash);
void cd_to_home(data_shell *datash);

/* cd_shell.c */
int cd_shell(data_shell *datash);

/* get_builtin */
int (*get_builtin(char *cmd))(data_shell *datash);

/* _exit.c */
int exit_shell(data_shell *datash);

/* aux_stdlib.c */
int get_len(int n);
char *aux_itoa(int n);
int _atoi(char *s);

/* aux_error1.c */
char *strcat_cd(data_shell *, char *, char *, char *);
char *error_get_cd(data_shell *datash);
char *error_not_found(data_shell *datash);
char *error_exit_shell(data_shell *datash);

/* aux_error2.c */
char *error_get_alias(char **args);
char *error_env(data_shell *datash);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(data_shell *datash);


/* get_error.c */
int get_error(data_shell *datash, int eval);

/* get_sigint.c */
void get_sigint(int signal);

/* aux_help.c */
void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);

/* aux_help2.c */
void aux_help(void);
void aux_help_alias(void);
void aux_help_cd(void);

/* get_help.c */
int get_help(data_shell *datash);

#endif
