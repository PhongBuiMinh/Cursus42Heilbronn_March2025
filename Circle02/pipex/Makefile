CC = gcc
FLAG = -Wall -Werror -Wextra -g

NAME = pipex
BONUS_NAME = pipex_bonus

COMMON_SRC = utils.c bonus_utils.c execution.c
SRC = pipex.c $(COMMON_SRC)
BONUS_SRC = pipex_bonus.c $(COMMON_SRC)

OBJ =  $(SRC:.c=.o)
BONUS_OBJ =  $(BONUS_SRC:.c=.o)

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

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ) | $(LIBFT)
	@$(CC) $(FLAG) $^ -L$(LIBFT_PATH) -lft -o $@

clean:
	@rm -f $(OBJ) $(BONUS_OBJ)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME) $(FILEIN) $(FILEOUT)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: fclean clean re all
