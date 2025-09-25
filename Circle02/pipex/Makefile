CC = gcc
FLAG = -Wall -Werror -Wextra -g

NAME = pipex
SRC = pipex.c utils.c
OBJ =  $(SRC:.c=.o)

FILEIN = filein
FILEOUT = fileout

INCLUDE = -I../minitalk/libft
LIBFT_PATH = ../minitalk/libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

%.o: %.c
	@$(CC) $(FLAG) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJ) | $(LIBFT)
	@$(CC) $(FLAG) $^ -L$(LIBFT_PATH) -lft -o $@

clean:
	@rm -f $(OBJ)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@rm -f $(NAME) $(FILEIN) $(FILEOUT)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: fclean clean re all
