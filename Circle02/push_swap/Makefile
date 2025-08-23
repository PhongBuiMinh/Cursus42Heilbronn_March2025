# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/27 13:31:52 by fbui-min          #+#    #+#              #
#    Updated: 2025/07/27 13:31:52 by fbui-min         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror -g
NAME = push_swap

SRC_DIR = src
SRC = push_swap.c \
		input_validation.c input_processing.c \
		monitoring.c \
		algorithm.c algorithm_utils.c \
		stack_management.c stack_utils.c stack_searching.c \
		push_ops.c swap_ops.c rotate_ops.c reverse_rotate_ops.c advanced_rotation.c
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Libraries
LIBFT = libft/libft.a
PRINTF = printf/printf.a

all: $(NAME)

$(LIBFT):
	@make bonus -C lib/libft

$(PRINTF):
	@make -C lib/printf

# Objs + includes
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(FLAGS) -Iincludes -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Libs + link
$(NAME): $(OBJ) $(LIBFT) $(PRINTF)
	@$(CC) $(FLAGS) $(OBJ) -Llib/libft -lft -Llib/printf -lprintf -o $@
	@echo "$(NAME) compiled successfully."

clean:
	@make clean -C lib/printf; make clean -C lib/libft
	@rm -rf $(OBJ_DIR)
	@echo "Object files cleaned."

fclean: clean
	@make fclean -C lib/printf; make fclean -C lib/libft
	@rm -f $(NAME)
	@echo "Full clean complete.	"

re: fclean all

.PHONY: fclean clean re all
