CC = gcc
FLAG = -Wall -Werror -Wextra -g

NAME = pipex
BONUS_NAME = pipex_bonus

COMMON_SRC = utils.c execution.c
SRC = pipex.c $(COMMON_SRC)
BONUS_SRC = pipex_bonus.c $(COMMON_SRC)

OBJ =  $(SRC:.c=.o)
BONUS_OBJ =  $(BONUS_SRC:.c=.o)

FILEIN = filein
FILEOUT = fileout

INCLUDE = -I../minitalk/libft -I../../Circle01/get_next_line

GET_NEXT_LINE_PATH = ../../Circle01/get_next_line
GET_NEXT_LINE = $(GET_NEXT_LINE_PATH)/get_next_line.a

LIBFT_PATH = ../minitalk/libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(GET_NEXT_LINE):
	@make -C $(GET_NEXT_LINE_PATH)

%.o: %.c
	@$(CC) $(FLAG) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJ) | $(LIBFT)
	@$(CC) $(FLAG) $^ -L$(LIBFT_PATH) -lft -o $@

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ) | $(LIBFT) $(GET_NEXT_LINE)
	@$(CC) $(FLAG) $^ $(GET_NEXT_LINE) -L$(LIBFT_PATH) -lft -o $@

clean:
	@rm -f $(OBJ) $(BONUS_OBJ)
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(GET_NEXT_LINE_PATH)

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME) $(FILEIN) $(FILEOUT)
	@make fclean -C $(LIBFT_PATH)
	@make fclean -C $(GET_NEXT_LINE_PATH)

re: fclean all

.PHONY: fclean clean re all
