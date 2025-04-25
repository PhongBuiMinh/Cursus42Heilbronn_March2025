/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phong <phong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:24:50 by fbui-min          #+#    #+#             */
/*   Updated: 2025/04/25 13:16:23 by phong            ###   ########.fr       */
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
	size_t			part_len; // partial line length
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
void	update_leftover(char *buffer);
char	*extract_line(t_list *lst);
void	append_to_list(t_list **head, char *buffer);

void	ft_lstclear(t_list **lst);
char	*ft_strdup(const char *s1);
size_t	calculate_line_length(t_list *list);
bool	has_new_line(t_list *lst);

#endif