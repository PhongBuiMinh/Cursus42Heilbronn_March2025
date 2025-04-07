CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
SRC = ft_printf.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar -rsc $(NAME) $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

fclean:
	rm -f $(OBJ) $(NAME)

clean:
	rm -f $(OBJ)

re: fclean all

.PHONY: fclean re clean all
