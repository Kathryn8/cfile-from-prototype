#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <stdarg.h>

extern char **environ;

/**
 * struct data_type - dt for short
 * @short: string
 * @long: string
 *
 * Description: stores c lang data type with corresponding long form name
 */
typedef struct data_type
{
	char *short_name;
	char *long_name;
} dt_t;

/* shell.c file contents: */
int is_executable(char *string);
void get_input(char **buffer, size_t *bufsize, ssize_t *getret);
void assign_words_to_array(char *str, char *argv[]);
int fork_child_adult(char **argv, char **environ, char **str);

/* get_path.c file contents: */
void split_string_into_words(char *string, char **words);
char *get_env_string(char *env_key);
char *get_executable_string(char *path, char *program_name);
char *get_path(char **name, char *program_name);

/* helper_functions.c file contents: */
int builtin_commands(char **argv, char **environ, int *status, char *str);
int print_env(char *envp[]);
DIR *_opendir(char *name);
struct dirent *_readdir(DIR *dp);

#endif /* __MAIN_H__ */
