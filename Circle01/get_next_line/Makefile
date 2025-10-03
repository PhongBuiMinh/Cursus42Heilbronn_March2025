# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/16 14:27:21 by fbui-min          #+#    #+#              #
#    Updated: 2025/04/25 22:29:51 by fbui-min         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GCC = cc
CFLAGs = -Wall -Wextra -Werror
SRCs = get_next_line.c \
		get_next_line_utils.c
OBJs = $(SRCs:.c=.o)
NAME = get_next_line.a

all: $(NAME)

$(NAME): $(OBJs)
	@ar -src $(NAME) $(OBJs)

%.o: %.c
	$(GCC) $(CFLAGs) -c $< -o $@

clean:
	@rm -f $(OBJs)

fclean:
	@rm -f $(NAME) $(OBJs)

re: fclean all

.PHONY: clean fclean re all

# program: test1.txt get_next_line.c get_next_line_utils.c
# 	@$(GCC) $(CFLAGs) -D BUFFER_SIZE=10 -g -o program $(SRCs)
