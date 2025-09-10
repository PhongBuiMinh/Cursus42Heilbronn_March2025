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

GREEN = \033[0;32m
RED = \033[0;31m
DEFAULT = \033[0m

NAME = fractol
CC = gcc
FLAG = -Wall -Wextra -Werror -g

OS_TYPE := $(shell uname -s)
ifeq ($(OS_TYPE),Darwin)
	MLX_PATH = lib/minilibx-macos
	MLX_TAR = minilibx_macos_opengl.tgz
	MLX_FLAG = -framework OpenGL -framework AppKit
else ifeq ($(OS_TYPE),Linux)
	MLX_PATH = lib/minilibx-linux
	MLX_TAR = minilibx-linux.tgz
	MLX_FLAG = -lXext -lX11 -lm -lz
endif
LIBFT_PATH = lib/libft

# Libraries
LIBFT = lib/libft/libft.a
MLX = $(MLX_PATH)/libmlx.a

# RECOURSE
SRC_DIR = src
SRC = fractol.c \
		init.c input_output.c \
		hook_handler.c compute_fractal.c
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(LIBFT):
	@echo "$(GREEN)Building libft library...$(DEFAULT)"
	@make -C lib/libft

$(MLX):
	@echo "$(GREEN)Building mlx library...$(DEFAULT)"
	@tar -xvzf $(MLX_TAR) -C lib
ifeq ($(OS_TYPE),Darwin)
	mv lib/minilibx_opengl_20191021 $(MLX_PATH)
endif
	@make -C $(MLX_PATH)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c include/fractol.h | $(OBJ_DIR)
	@echo "$(GREEN)Compling source files...$(DEFAULT)"
	@$(CC) $(FLAG) -Iinclude -I$(LIBFT_PATH) -I$(MLX_PATH) -c $< -o $@

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@echo "$(GREEN)Linking files...$(DEFAULT)"
	@$(CC) $(FLAG) $(OBJ) -L$(LIBFT_PATH) -lft -L$(MLX_PATH) -lmlx $(MLX_FLAG) -o $@

clean:
	@echo "$(RED)Removing object files...$(DEFAULT)"
	@rm -rf $(OBJ_DIR)
	@make clean -C $(MLX_PATH)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@echo "$(RED)Removing program and libraries...$(DEFAULT)"
	@rm -f $(NAME)
	@rm -rf $(MLX_PATH)
	@make fclean -C $(LIBFT_PATH)

# wget https://cdn.intra.42.fr/document/document/37672/minilibx_macos_metal.tgz -O minilibx-linux.tgz
# curl -o minilibx-linux.tgz https://cdn.intra.42.fr/document/document/37672/minilibx_macos_metal.tgz
