# C file from prototype program

#### Welcome to a simple program that I wrote for fun as well as to speed up writing code solutions for Holberton software engineering course projects.
The first trimester of Holberton is focused on learning C language and many of the tasks require us to write a function. Often the function prototype is provided in the question. With just this single string of text, we can extract enough data to produce a simple template file.

### Installation
`git clone` into your local directory and type `make`. This will create an executable called create_cfile. To be able to access the program from any directory, add it's location to your PATH variable or move the executable to one of directories already in your PATH. I moved mine to `/usr/local/bin`.

### Usage

Function prototype must always be in double quotes.

`$ ./create_comments "void print_error(stack_t **stack, unsigned int line_num)"`
This will produce the following to standard output:
```
/**
 * print_error - short description
 * @stack: a stack_t **data type variable
 * @line_num: a unsigned int data type variable
 *
 * Return: type is void
 */

void print_error(stack_t **stack, unsigned int line_num)
{
	;
}
```

You can also use the option `-f` to create a file with the function name:


