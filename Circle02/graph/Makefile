# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/01 16:14:51 by fbui-min          #+#    #+#              #
#    Updated: 2025/09/01 16:14:51 by fbui-min         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = gcc
FLAG = -Wall -Wextra -Werror -g

SRC_DIR = src
SRC = fractol.c
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Libraries
LIBFT = libft.a
MLX = libmlx.a

all: $(NAME)

$(LIBFT):
	@make -C lib/libft

$(MLX):
	@tar -xvzf minilibx_macos_opengl.tgz -C lib && mv lib/minilibx_opengl_20191021 lib/minilibx-macos
	@make -C lib/minilibx-macos
# tar -xvzf minilibx-linux.tgz -C lib
# make -C lib/minilibx-linux

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(FLAG) -Iinclude -Ilib/libft -Ilib/minilibx-macos -c $< -o $@
# $(CC) $(FLAG) -Ilib/libft -Ilib/minilibx-linux -c $< -o $@

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@$(CC) $(FLAG) $(OBJ) -Llib/libft -lft -Llib/minilibx-macos -lmlx -framework OpenGL -framework AppKit -o $@
# $(CC) $(FLAG) $(OBJ) -Llib/libft -lft -Llib/minilibx-linux -lmlx -lXext -lX11 -lm -lz -o $@

clean:
	@make clean -C lib/libft
	@rm -rf $(OBJ_DIR)
	@make clean -C lib/minilibx-macos
# make clean -C lib/minilibx-linux

fclean: clean
	@rm -f $(NAME)
	@make fclean -C lib/libft
	@cd lib && rm -rf minilibx-macos
# cd lib && rm -rf minilibx-linux

