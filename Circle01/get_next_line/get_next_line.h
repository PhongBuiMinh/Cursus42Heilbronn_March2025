/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phong <phong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:24:50 by fbui-min          #+#    #+#             */
/*   Updated: 2025/04/21 20:51:12 by phong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

# include <stdio.h>
# include <string.h>

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);

#endif