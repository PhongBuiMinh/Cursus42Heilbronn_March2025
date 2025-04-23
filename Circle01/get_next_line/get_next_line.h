/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:24:50 by fbui-min          #+#    #+#             */
/*   Updated: 2025/04/23 18:47:27 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
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
void	ft_lstclear(t_list **lst);

char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
size_t	calculate_line_length(t_list *list);
t_list	*ft_lstlast(t_list *list);

#endif