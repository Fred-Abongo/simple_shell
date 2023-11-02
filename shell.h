#ifndef _SHELL_H_
#define _SHELL_H_


#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>


/* READ & WRITE BUFFERS */
#define BUF_FLUSH -1
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024


/* COMMAND CHAINING */
#define CMD_CHAIN	3
#define CMD_NORM	0
#define CMD_AND		2
#define CMD_OR		1


/* convert_number() function */
#define CONVERT_UNSIGNED	2
#define CONVERT_LOWERCASE	1


/* choice 1 if using system getline() function */
#define USE_STRTOK 0
#define USE_GETLINE 0

#define HIST_MAX	4096
#define HIST_FILE	".simple_shell_history"

extern char **environ;

/**
 * struct liststr - Its a singly linked list
 * @numb: Its a number field
 * @str: The string
 * @next: Next node pointer
 */

typedef struct liststr
{
	int numb;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - Contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @input_string: A string generated from getline containing arguements
 * @input_array: An array of strings generated from arg
 * @current_path: A string path for the current command
 * @argument_count: The argument count
 * @error_count: The error count
 * @error_code: The error code for exit()s
 * @count_current_line: If on count this line of input
 * @program_filename: The program filename
 * @env_variables: Linked list local copy of environ
 * @modified_env_viriable: Custom modified copy of
 * environment from LL environment variable
 * @history_list: The history node
 * @alias_list: The alias node
 * @environment_changed: On if environ was changed
 * @command_status: The return status of the last exec'd command
 * @command_buffer: Address of pointer to cmd_buf, on if chaining
 * @command_buffer_type: CMD_type ||, &&, ;
 * @read_file_descriptor: The fd from which to read line input
 * @history_line_number_count: The history line number count
 */
typedef struct passinfo
{
	char *input_string;
	char **input_array;
	char *current_path;
	int argument_count;
	unsigned int error_count;
	int err_code;
	int count_current_line;
	char *program_filename;
	list_t *env_variable;
	list_t *history_list;
	list_t *alias_list;
	char **modified_env_variable;
	int environment_changed;
	int command_status;

	char **command_buffer;
	int command_buffer_type;
	int read_file_descriptor;
	int hist_line_count;
} info_t;


#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - It contains builtin string and related function
 * @type: Builtin command flag
 * @func: Function
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* ShellLoopsKS.c components*/
int shell_loop(info_t *, char **);
int find_builtin(info_t *);
void cmd_find(info_t *);
void cmd_fork(info_t *);

/* ShellParserKS.c components*/
int is_exe_cmd(info_t *, char *);
char *dups_chars(char *, int, int);
char *path_finder(info_t *, char *, char *);

/* ShellErrorsKS.c components */
void eput_str(char *);
int eput_char(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* ShellListsKS1.c components */
size_t list_length(const list_t *);
char **list_strings(list_t *);
size_t printed_list(const list_t *);
list_t *node_startswith(list_t *, char *, char);
ssize_t node_index(list_t *, list_t *);

/* ShellExitsKS.c components */
char *str_n_cpy(char *, char *, int);
char *str_n_cat(char *, char *, int);
char *str_chr(char *, char);

/* TokensGenKS.c components */
char **string_to_words(char *, char *);
char **string_to_words1(char *, char);

/* MemReallocKS.c components */
char *memory_set(char *, char, unsigned int);
void str_free(char **);
void *mem_realloc(void *, unsigned int, unsigned int);

/* GetInfoKS.c components */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* ShellErrorsKS1.c components */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_num(long int, int, int);
void remove_comments(char *);

/* ShellStringsKS.c components */
int str_len(char *);
int str_cmp(char *, char *);
char *starts_with(const char *, const char *);
char *str_cat(char *, char *);

/* ShellStringsKS1.c components */
char *str_cpy(char *, char *);
char *str_dup(const char *);
void _puts(char *);
int _putchar(char);

/* ShellListsKS.c components */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* ShellIntConverterKS.c components */
int is_interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int string_to_int(char *);

/* GetLineKS.c components */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* EnvironsKS.c components */
char *get_env(info_t *, const char *);
int my_env(info_t *);
int my_set_env(info_t *);
int my_unset_env(info_t *);
int pop_env_list(info_t *);

/* GetEnvKS.c components */
char **get_environ(info_t *);
int unset_env(info_t *, char *);
int set_env(info_t *, char *, char *);

/* ShellMemoriesKS.c components */
int pntr_free(void **);

/* BuiltinShellKS.c components */
int shl_exit(info_t *);
int _cwd(info_t *);
int _cpd(info_t *);

/* BuiltinShellKS1.c components */
int hist_list(info_t *);
int _myalias(info_t *);

/* ShellHistoryKS.c components */
char *get_hist_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_hist_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* ShellVarsKS.c components */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int alias_rep(info_t *);
int vars_rep(info_t *);
int str_rep(char **, char *);

#endif
