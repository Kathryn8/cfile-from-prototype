CC = gcc
SRC = main.c
OBJ = $(SRC:.c=.o)
NAME = create_comments
RM = rm
CFLAGS = -Wall -Werror -Wextra -pedantic

all: $(OBJ)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

test:
	$(CC) $(SRC) -o $(NAME)

clean:
	$(RM) -f *~ $(NAME)

oclean:
	$(RM) -f $(OBJ)

fclean: clean oclean

re: oclean all
