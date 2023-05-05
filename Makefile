CC = gcc
SRC = main.c
OBJ = $(SRC:.c=.o)
NAME = create_cfile
RM = rm
CFLAGS = -Wall -Werror -Wextra -pedantic

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

test: $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) -f *~ $(NAME)

oclean:
	$(RM) -f $(OBJ)

fclean: clean oclean

re: oclean all
