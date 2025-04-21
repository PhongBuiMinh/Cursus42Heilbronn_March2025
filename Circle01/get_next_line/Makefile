# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phong <phong@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/16 14:27:21 by fbui-min          #+#    #+#              #
#    Updated: 2025/04/20 23:06:48 by phong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GCC = cc
CFLAGs = -Wall -Wextra -Werror
SRCs = get_next_line.c \
		get_next_line_utils.c
OBJs = $(SRCs:.c=.o)
NAME = get_next_lineft.a

all: $(NAME)

$(NAME): $(OBJs)
	@ar -src $(NAME) $(OBJs)

%.o: %.c
	@$(GCC) $(CFLAGs) -c $< -o $@

clean:
	@rm -f $(OBJs)

fclean:
	@rm -f $(NAME) $(OBJs)

re: fclean all

.PHONY: clean fclean re all

program:
	@$(GCC) $(CFLAGs) -D BUFFER_SIZE=5 $(SRCs)

