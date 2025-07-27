# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/17 13:19:21 by fbui-min          #+#    #+#              #
#    Updated: 2025/07/17 22:20:15 by fbui-min         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra
NAME = server client
NAME_BONUS = server_bonus client_bonus

SRC = server.c client.c
OBJ = $(SRC:.c=.o)
BONUS = server_bonus.c client_bonus.c
BONUSOBJ = $(BONUS:.c=.o)

# Include paths for compilation
INCLUDES = -Ilibft -Iprintf

LIBFT = libft/libft.a
PRINTF = printf/libftprintf.a

all: $(NAME)

bonus: $(NAME_BONUS)

# Object file compilation
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make bonus -C libft

$(PRINTF):
	make -C printf

# Linking
server: server.o $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $< -Llibft -lft -Lprintf -lftprintf -o $@

client: client.o $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $< -Llibft -lft -Lprintf -lftprintf -o $@

# Bonus linking
server_bonus: server_bonus.c $(BONUSOBJ) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $< -Llibft -lft -Lprintf -lftprintf -o server

client_bonus: client_bonus.c $(BONUSOBJ) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $< -Llibft -lft -Lprintf -lftprintf -o client

clean:
	make clean -C printf; make clean -C libft
	rm -f $(OBJ) $(BONUSOBJ)

fclean:
	make fclean -C printf; make fclean -C libft
	rm -f server client server_bonus client_bonus $(OBJ) $(BONUSOBJ)

re: fclean all
