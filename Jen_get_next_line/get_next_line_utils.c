/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschuste <jschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:38:51 by jschuste          #+#    #+#             */
/*   Updated: 2025/06/11 17:13:19 by jschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		t;

	t = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (str)
		str[ft_strlen(s1)] = '\0';
	else
		return (NULL);
	while (s1[t])
	{
		str[t] = s1[t];
		t++;
	}
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		s1_len;
	size_t	i;

	s1_len = ft_strlen(s1);
	i = -1;
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc((sizeof (char))
			* (s1_len) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	i = -1;
	while (s2[++i])
		str[s1_len + i] = s2[i];
	str[s1_len + i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	len_str;

	if (!s)
		return (NULL);
	len_str = ft_strlen(s);
	if (len > len_str)
		len = len_str;
	if (start + len > len_str)
		len = len_str - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_memmove(str, s + start, len);
	str[len] = '\0';
	return (str);
}

void	ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (dest == NULL && src == NULL)
		return ;
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = len;
	if (dest > src)
	{
		while (i > 0)
		{
			d[i - 1] = s[i -1];
			i--;
		}
	}
	else if (dest < src)
	{
		while (i > 0)
			*d++ = *s++;
	}
}
// char	*ft_strchr(const char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	if (s)
// 	{
// 		while (s[i] != '\0')
// 		{
// 			if (s[i] == (unsigned char)c)
// 				return ((char *)(s + i));
// 			i++;
// 		}
// 	}
// 	if ((unsigned char)c == '\0')
// 		return ((char *)(s + i));
// 	return (0);
// }

// static void	*ft_memcpy_local(void *dest, const void *src, size_t n)
// {
// 	size_t				i;
// 	unsigned char		*d;
// 	const unsigned char	*s;

// 	d = (unsigned char *)dest;
// 	s = (const unsigned char *)src;
// 	i = 0;
// 	while (i < n)
// 	{
// 		d[i] = s[i];
// 		i++;
// 	}
// 	return (dest);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*joinstr;
// 	size_t	len1;
// 	size_t	len2;

// 	if (!s1 && !s2)
// 		return ("");
// 	if (!s2)
// 		return (s1);
// 	if (!s1)
// 		return (s2);
// 	len1 = ft_strlen(s1);
// 	len2 = ft_strlen(s2);
// 	joinstr = (char *)malloc(len1 + len2 + 1);
// 	if (!joinstr)
// 		return (NULL);
// 	ft_memcpy_local(joinstr, s1, len1);
// 	ft_memcpy_local(joinstr + len1, s2, len2);
// 	joinstr[len1 + len2] = '\0';
// 	return (joinstr);
// }

// char	*ft_substr(const char *s, unsigned int start, size_t len)
// {
// 	char	*sub;
// 	size_t	s_len;
// 	size_t	i;

// 	if (!s)
// 		return (NULL);
// 	s_len = ft_strlen(s);
// 	if (start >= s_len)
// 	{
// 		sub = malloc(1);
// 		if (!sub)
// 			return (NULL);
// 		return (sub[0] = '\0', sub);
// 	}
// 	if (len > s_len - start)
// 		len = s_len - start;
// 	sub = malloc(len + 1);
// 	if (!sub)
// 		return (NULL);
// 	i = -1;
// 	while (++i < len)
// 		sub[i] = s[start + i];
// 	return (sub[i] = '\0', sub);
// }
