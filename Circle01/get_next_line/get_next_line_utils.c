/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phong <phong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:27:08 by fbui-min          #+#    #+#             */
/*   Updated: 2025/04/20 21:45:32 by phong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	len;

	len = -1;
	while (s[++len]);
	return (len);
}

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	i;

	dst = malloc(ft_strlen(s1) + 1);
	if (dst == NULL || s1 == NULL)
		return (NULL);
	
	i = -1;
	while (s1[++i])
		dst[i] = s1[i];

	dst[i] = '\0';
	return (dst);
}
