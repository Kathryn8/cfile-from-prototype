#include "main.h"

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
	char *prototype_string = NULL;
	char *string_for_sections;
	int file_print_flag;

	check_arg_count(ac, av[0]);
	file_print_flag = check_arguments(av);
	string_for_sections = get_user_prototype_string(file_print_flag, &prototype_string, av);
	num_sections = split_prototype_into_sections(string_for_sections, sections);
	function_name = get_function_name(sections[0]);
	fd = set_output_steam(file_print_flag, function_name);
	dprintf(fd, "/**\n * %s - short description\n", function_name);
	if (sections[1] == NULL && num_sections == 1)
	{
		sections[1] = "void";
		modify_prototype_string(&prototype_string);
	}
	if (strcmp(sections[1], "void") == 0)
	{
		num_sections = 1;
	}
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
	return_type = get_return_type(sections[0]);
	generate_comments(fd, return_type, prototype_string);
	free(function_name);
	free(return_type);
	free(prototype_string);
	free(string_for_sections);
	if (file_print_flag == FILE)
	{
		close(fd);
	}
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

int check_arguments(char **av)
{
	int flag;
	char *input_string;

	if (strcmp(av[1], "-f") == 0)
	{
		flag = FILE;
		input_string = av[2];
	}
	else
	{
		flag = PRINT;
		input_string = av[1];
	}
	if (strchr(input_string, '(') == NULL || strchr(input_string, ')') == NULL)
	{
		printf("Please provide a function prototype in the correct format\n");
		exit (1);
	}
	return (flag);
}
void check_arg_count(int ac, char *filename)
{
	if (ac < 2 || ac > 3)
	{
		printf("\n\t\tUsage: %s \"function prototype in double quotes\"\n", filename);
		printf("\t\toption '-f' to create a file, default prints to standard output\n\n");
		exit (1);
	}
	;
}

int set_output_steam(int file_print_flag, char *function_name)
{
	char *file_name;
	int fd;

	if (file_print_flag == FILE)
	{
		file_name = get_file_name(function_name);
		fd = open(file_name, O_CREAT | O_EXCL | O_WRONLY, 0664);
		free(file_name);
		if (fd == -1)
		{
			perror("Cannot create file");
			exit (1);
		}
		return (fd);
	}
	else
	{
		fd = STDOUT_FILENO;
		return (fd);
	}
}

void generate_comments(int fd, char *return_type, char *string)
{
	dprintf(fd, " *\n * Return: type is %s\n */\n\n", return_type);
	dprintf(fd, "%s\n", string);
	if (strncmp(return_type, "void", 4) == 0)
	{
		dprintf(fd, "{\n\t;\n}\n");
	}
	else
	{
		dprintf(fd, "{\n\t%sreturn_value;\n\n", return_type);
		dprintf(fd, "\treturn (return_value);\n}\n");
	}
}

char *get_user_prototype_string(int file_print_flag, char **prototype_string, char **av)
{
	char *string_for_sections = NULL;

	if (file_print_flag == PRINT)
	{
		*prototype_string = strdup(av[1]);
	}
	else
	{
		*prototype_string = strdup(av[2]);
	}
	string_for_sections = strdup(*prototype_string);
	return (string_for_sections);
}

void modify_prototype_string(char **prototype_string)
{
	char *ptr;
	size_t size, len, index;

	ptr = strstr(*prototype_string, "()");
	if (ptr == NULL)
	{
		printf("Please provide a function prototype in the correct format (parameter format error)\n");
		exit (1);
	}
	len = strlen(*prototype_string);
	size = (sizeof(char) * len + 4);
	*prototype_string = realloc(*prototype_string, size);
	index = len - 1;
	*(*prototype_string + index) = '\0';
	strcat(*prototype_string, "void");
	strcat(*prototype_string, ")");
}
