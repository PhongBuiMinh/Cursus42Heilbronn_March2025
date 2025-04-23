/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phong <phong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:27:08 by fbui-min          #+#    #+#             */
/*   Updated: 2025/04/22 20:41:13 by phong            ###   ########.fr       */
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
	dst = malloc(len + 1);
	if (!dst)
		return (NULL);
	i = -1;
	while (s1[++i])
		dst[i] = s1[i];
	dst[i] = '\0';
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	newc;
	int				i;

	newc = (unsigned char)c;
	i = -1;
	while (s[++i])
	{
		if (s[i] == newc)
			return ((char *)&s[i]);
	}
	if (newc == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
