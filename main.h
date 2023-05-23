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

#define MAX 10
#define PRINT 0
#define FILE 1

int split_prototype_into_sections(char* prototype, char** sections);
char *get_function_name(char *section);
char *get_return_type(char *section);
void rev_string(char *s);
char *get_file_name(char *function_name);
int check_arguments(char **av);
void check_arg_count(int ac, char *filename);
int set_output_steam(int file_print_flag, char *function_name);
void generate_comments(int fd, char *return_type, char *string);
char *get_user_prototype_string(int file_print_flag, char **prototype_string, char **av);
void modify_prototype_string(char **prototype_string);

#endif /* __MAIN_H__ */
