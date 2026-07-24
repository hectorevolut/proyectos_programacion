CC = clang
CFLAGS = -Wall -Wextra -Werror -std=c11 -Iinclude
SRC = src/movimientos.c src/main.c
OBJ = $(SRC:.c=.o)
NAME = c-core

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re