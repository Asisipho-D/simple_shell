#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fontl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* foor convert_number() */
#define CONVERT_LOWERCASE        1
#define CONVERT_UNSIGNED         2

/* 1 if using sysytem getline() */
#define USE_GETLINE  0
#define USE_STRTOK   0

#define HIST_FILE        ".simple_shell_history"
#define HIST_MAX         4096

extern char **environ;


/**
 * struct strlist - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct strlist
{
	int num;
	char *str;
	struct strlist *next;
} List_t;

/**
 * struct passdetails - contains pseudo-arguuments to pass into a function,
 *                allowing uniform prototyppe for function pointer struct
 *@arg: a string generated from getline containing arguments
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@agc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alis node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passdetails
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	List_t *env;
	List_t *history;
	List_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory management */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} details_t;

#define DETAILS_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL,\
	0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @ func: the function
 */
typdef struct builtin
{
	char *type;
	int (*func) (details_t *);
} builtin_table;
	
/* toem_shloop.c */
int hsh (details_t *, char **);
int find_builtin(details_t *);
void find_cmd(details_t *);
void fork_cmd(details_t *);

/* toem_parser.c */
int is_cmd(details_t *, char **);
char *dup_chars(char *, int, int);
char *find_path(details_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strncpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int interactive(details_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_errors1.c */
int errotoi(char *);
void print_error(details_t *, char *); 
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int _myexit(details_t *);
int _mycd(details_t *);
int _myhelp(details_t *);

/* toem_builtin1.c */
int _myhistory(details_t *);
int _myalias(details_t *);

/* toem_getline.c */
ssize_t get_input(details_t *);
int _getline(details_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getdetails.c */
void clear_details(details_t *);
void set_details(details_t *, char **);
void free_details(details_t *, int);

/* toem_environ.c */
char *_getenv(details_t *, const char *);
int _myenv(details_t *);
int _mysetenv(details_t *);
int _myunsetenv(details_t *);
int populate_env_list(details_t *);

/* toem_getenv.c */
char **get_environ(details_t *);
int _unsetenv(details_t *, char *);
int _setenv(details_t *, char *, char *);

/* toem_history.c */
char *get_history_file(details_t *details);
int write_history(details_t *details);
int read_history(details_t *details);
int build_history_list(details_t *details, char *buf, int linecount);
int renumber_history_list(details_t *details);

/* toem_lists.c */
List_t *add_node(List_t **, const char *, int);
List_t *add_node_end(List_t **, const char *, int);
Size_t print_list_str(const List_t *);
int delete_node_@index(List_t **, unsigned int);
void free_list(List_t **);

/* toem_list1.c */
Size_t List_len(const List_t *);
char **List_to_strings(List_t *);
Size_t print_list(const List_t *);
List_t *node_starts_with(List_t *, char *, char);
ssize_t get_node_index(List_t *, List_t *);

/* toem_vars.c */
int is_chain(details_t *, char *, Size_t *, Size_t *);
void check_chain(details_t *, char *,Size_t *, Size_t *);
int replace_alias(details_t *);
int replace_vars(details_t *);
int replace_string(char **, char *);

#endif
