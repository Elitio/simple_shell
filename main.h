#ifndef _MAIN_
#define _MAIN_



/* standard library of functions */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <dirent.h>

#define SIZE_OFBUF 1024
#define TOK_SIZE_OFBUF 128
#define DEL_TOKEN " \t\r\n\a"

extern char **environ;



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
	int status;
	char *pid;
	int counter;
	char **av;
	char **args;
	char **_environ;
} data_shell;




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
 * struct builtin_s - Builtin structure for command arguments.
 * @name: command builtin name
 * @f: pointer func of data type
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *shell_data);
} builtin_t;







/*function edits */
int command_err(char *direct, data_shell *shell_data);
char *find_pth(char *inp_cmd, char **_environ);
int _execute(data_shell *shell_data);
int chk_dir(char *str_path, int *cur_pos_ind);
int can_exec(data_shell *shell_data);
void printInError(data_shell *shell_data, char *inp_str, int ind,
		int isSingle);
int chkChar(char *inp_str, int *ind);
int repChar(char *inp_str, int ind);
int sepError(char *inp_str, int ind, char ind_sep_end);
int chkInEror(data_shell *shell_data, char *inp_str);
void plusNode(sep_list **sepHead, line_list **cmdHead, char *inp_str);
char **splitIn(char *inp_str);
void nxtFunc(sep_list **sepHead, line_list **cmdHead, data_shell *shell_data);
char *chSwap(char *inp_str, int isZero);
int spltCmdFunc(data_shell *shell_data, char *inp_str);
int (*isBuiltInF(char *cmd))(data_shell *);





int get_value_length(char *value);
int get_command_length(char *command);
int custlenStrF(char *str_inp);
int is_var_empty(r_var *pointr);
int is_val_empty(r_var *pointr);
int copy_var_val_to_new_input(r_var *pointr, char *new_input, int i);
int skip_var_in_input(r_var *pointr);
void printInError(data_shell *datash, char *input, int i, int bool);


/*old functions added */
void chkEnvF(r_var **strnode, char *user_inp, data_shell *struct_info);



int chkVarsF(r_var **strnode, char *user_inp, char *str_stat,
		data_shell *struct_info);

void setDataF(data_shell *shell_data, char **arg_vector);

void freeDataF(data_shell *shell_data);
char *remCommentF(char *input_str);

void sh_loopF(data_shell *data_shell_info);

void getSigF(int signal);

char *replaceInputF(r_var **strNode, char *str_inp, char *replaced_str,
int len_new);

char *repVarFnc(char *str_inp, data_shell *struct_info);

ssize_t getLineF(char **lineptr, size_t *n, FILE *stream);

char *callGetLineF(int *is_end_of_file);

void cdDotF(data_shell *shell_data);

void cdPrevF(data_shell *shell_data);

void cdHomeF(data_shell *shell_data);

void cdToDirF(data_shell *shell_data);

int cdHandlerF(data_shell *data_shell);

int cpmStrF(char *first_str, char *second_str);
int StrSpanF(char *string, char *checkn_str);
char *catStrF(char *str_dest, const char *str_source);
char *chrStrF(char *string, char charac);
char *cpyStrF(char *str_dest, char *str_source);
void strRevF(char *string);
int charCmpF(char string[], const char *delim);
char *tokStrF(char string[], const char *delim);
char *dupStrF(const char *string);
int lenStrF(const char *string);
int _isdigit(const char *string);
char *intToStrF(int inp_int);
int csAtoiF(char *str_wth_digs);
int lenGetF(int inp_int);
void cpyMemF(void *dest_ptr, const void *src_ptr, unsigned int cpy_size);
char **reallocDpF(char **array_ptr, unsigned int prev_size,
		unsigned int realloc_size);
void *reallocFnc(void *inp_buffer, unsigned int prev_size,
		unsigned int realloc_size);
void freeVarLstF(r_var **head);
r_var *add_rvar_node(r_var **head, int var_len, char *var_val, int val_len);
void free_sep_list(sep_list **head);
void free_line_list(line_list **head);
sep_list *add_sep_node_end(sep_list **head, char separat);
line_list *add_line_node_end(line_list **head, char *ptr_line);
int getErrorF(data_shell *shell_data, int error_ref);
char *errNotFoundF(data_shell *shell_data);
char *envErrorF(data_shell *shell_data);
char *exitShErrorF(data_shell *shell_data);
char *error126F(data_shell *shell_data);
char *cdErrorFun(data_shell *shell_data);
int extShFnc(data_shell *shell_data);
int _setenv(data_shell *shell_data);
char *copy_info(char *env_name, char *env_value);
void set_env(char *env_name, char *env_value, data_shell *shell_data);
int _unsetenv(data_shell *shell_data);
char *_getenv(const char *name_inp, char **_environ);
int _env(data_shell *shell_data);
int cmpEnvNameF(const char *env_var_name, const char *name_input);


int exec_line(data_shell *shell_data);
int cmpEnvNameF(const char *env_var_name, const char *name_input);



#endif
