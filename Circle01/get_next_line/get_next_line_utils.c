/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phong <phong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:27:08 by fbui-min          #+#    #+#             */
/*   Updated: 2025/04/25 00:55:51 by phong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		i;
	size_t	len;

	if (!s1)
		return (NULL);
	len = 0;
	while (s1[len])
		len++;
	dst = (char *)malloc((len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	i = -1;
	while (s1[++i])
		dst[i] = s1[i];
	dst[i] = '\0';
	return (dst);
}

size_t	calculate_line_length(t_list *lst)
{
	size_t	line_len;

	line_len = 0;
	if (!lst)
		return (line_len);
	while (lst)
	{
		line_len += lst->part_len;
		lst = lst->next;
	}
	return (line_len);
}

bool	has_new_line(t_list *lst)
{
	size_t	len;
	int		i;

	if (!lst)
		return (false);
	while (lst)
	{
		i = -1;
		len = 0;
		while (lst->str[++i] && lst->str[i] != '\n')
			len++;
		if (lst->str[i] == '\n')
		{
			len++;
			lst->part_len = len;
			return (true);
		}
		lst->part_len = len;
		lst = lst->next;
	}
	return (false);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*clean;

	while (*lst)
	{
		clean = *lst;
		*lst = (*lst)->next;
		free(clean->str);
		free(clean);
	}
	*lst = NULL;
}
