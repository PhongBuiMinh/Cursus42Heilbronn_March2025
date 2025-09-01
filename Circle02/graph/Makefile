# tar -xvzf minilibx-linux.tgz -C lib
NAME = fractol
CC = gcc
FLAG = -Wall -Wextra -Werror -g

SRC_DIR = src
SRC = fractol.c
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAG) -I../lib/minilibx-linux -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAG) $(OBJ) -L../lib/minilibx-linux -lmlx -lXext -lX11 -lm -lz -o $@

clean:
	make clean -C lib/minilibx-linux
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

# gcc -Wall -Wextra -Werror fractol.c -I../lib/minilibx-linux \
#     -L../lib/minilibx-linux -lmlx -lXext -lX11 -lm -lz -o fractol
# gcc -Wall -Wextra -Werror fractol.c -I../lib/minilibx-linux -L../lib/minilibx-linux -lmlx -lXext -lX11 -lm -lz -I../lib/libft -L../lib/libft -lft -o fractol
