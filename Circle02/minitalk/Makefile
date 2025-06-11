CC = gcc
CFLAGS = -Wall -Werror -Wextra
NAME = minitalk
SRC = server.c client.c
OBJ = $(SRC:.c=.o)
# Include paths for compilation
INCLUDES = -Ilibft -Iprintf

LIBFT = libft/libft.a
PRINTF = printf/libftprintf.a

all: $(NAME)

$(NAME): server client

# Object file compilation
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C libft

$(PRINTF):
	make -C printf

# Linking
server: server.o $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $< -Llibft -lft -Lprintf -lftprintf -o $@

client: client.o $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $< -Llibft -lft -Lprintf -lftprintf -o $@

clean:
	make clean -C printf; make clean -C libft
	rm -f server.o client.o

fclean:
	make fclean -C printf; make fclean -C libft
	rm -f server client server.o client.o

re: fclean all
