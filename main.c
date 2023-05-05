#include "main.h"
#define MAX 10

int split_prototype_into_sections(char* prototype, char** sections);
char *get_function_name(char *section);
char *get_return_type(char *section);
void rev_string(char *s);
char *get_file_name(char *function_name);

/**
 * main - a program to produce a c file from prototype
 * @ac: argument count
 * @av: user inputs as an array of strings
 *
 * Return: 0 upon success, 1 if error
 */

int main(int ac, char **av)
{
	char *sections[MAX];
	int num_sections, fd, i;
	char *function_name = NULL;
	char *return_type = NULL;
	char *variable_name = NULL;
	char *data_type = NULL;
	char *temp_prototype = NULL;
	char *file_name = NULL;

	if (ac != 2)
	{
		printf("\n\t\tUsage: %s \"function prototype in double quotes\"\n\n", av[0]);
		return (1);
	}
	if (strchr(av[1], '(') == NULL || strchr(av[1], ')') == NULL)
	{
		printf("Please provide a function prototype in the correct format\n");
		return (1);
	}
	temp_prototype = strdup(av[1]);
	num_sections = split_prototype_into_sections(temp_prototype, sections);
	function_name = get_function_name(sections[0]);
	return_type = get_return_type(sections[0]);
	file_name = get_file_name(function_name);
	fd = open(file_name, O_CREAT | O_WRONLY, 0664);
	free(file_name);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	dprintf(fd, "\t\t/********** %s.c file **********/\n\n", function_name);
	dprintf(fd, "/**\n * %s - short description\n", function_name);
	i = 1;
	while (i < num_sections)
	{
		variable_name = get_function_name(sections[i]);
		data_type = get_return_type(sections[i]);
		dprintf(fd, " * @%s: a %sdata type variable\n", variable_name, data_type);
		free(variable_name);
		free(data_type);
		i = i + 1;
	}
	dprintf(fd, " *\n * Return: type is %s\n */\n\n", return_type);
	dprintf(fd, "%s\n", av[1]);
	dprintf(fd, "{\n\t%sreturn_value;\n\n", return_type);
	dprintf(fd, "\treturn (return_value);\n}\n");
	free(function_name);
	free(return_type);
	free(temp_prototype);
	close(fd);
	return (0);
}

char *get_return_type(char *section)
{
	char *type;
	char *ptr;
	unsigned int len;

	rev_string(section);
	ptr = strchr(section, '*');
	if (ptr == NULL)
	{
		ptr = strchr(section, ' ');
	}
	if (ptr == NULL)
	{
		printf("Please provide a function prototype in the correct format (return type rror)\n");
		exit (1);
	}
	len = (section + strlen(section)) - ptr;
	rev_string(section);
	if (section[0] == ' ')
	{
		type = strndup((section + 1), len - 1);
	}
	else
	{
		type = strndup(section, len);
	}
	return (type);
}

char *get_function_name(char *section)
{
	char *name;
	char *ptr;
	unsigned int len;

	name = strdup(section);
	rev_string(name);
	ptr = strchr(name, '*');
	if (ptr == NULL)
	{
		ptr = strchr(name, ' ');
	}
	if (ptr == NULL)
	{
		printf("Please provide a function prototype in the correct format (function name error)\n");
		exit (1);
	}
	len = ptr - name;
	*(name + len) = '\0';
	rev_string(name);
	return (name);
}

int split_prototype_into_sections(char* prototype, char** sections)
{
	char* section = strtok(prototype, "(,);");
	int i = 0;

	while (section != NULL && i < (MAX - 1))
	{
		sections[i] = section;
		i = i + 1;
		section = strtok(NULL, "(,);");
	}
	sections[i] = NULL;
	if (i == 9)
	{
		printf("Warning: max number of arguments to function (10).\n");
	}
	return (i);
}

/**
 * rev_string - reverse a string
 * @s: takes parameter pointer to a char
 *
 * Return: void
 */

void rev_string(char *s)
{
	int length;
	int tmp;
	int i;

	length = strlen(s) - 1;
	i = 0;
	while (i <= (length / 2))
	{
		tmp = s[i];
		s[i] = s[length - i];
		s[length - i] = tmp;
		i = i + 1;
	}
}

char *get_file_name(char *function_name)
{
	char *name;

	name = malloc(sizeof(*name) * (strlen(function_name) + 4));
	if (name == NULL)
	{
		perror("malloc");
		exit(1);
	}
	strcat(name, "./");
	strcat(name, function_name);
	strcat(name, ".c");
	return (name);
}
