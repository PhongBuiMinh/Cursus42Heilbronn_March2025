CC = gcc
FLAG = -Wall -Werror -Wextra -g
NAME = pipex
SRC = pipex.c
OBJ =  $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(FLAG) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(FLAG) $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: fclean clean re all
