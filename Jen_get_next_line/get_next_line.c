/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschuste <jschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:37:25 by jschuste          #+#    #+#             */
/*   Updated: 2025/06/11 22:01:52 by jschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	find_newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*read_until_newline(int fd, char *leftover)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	int		nl_pos;
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(leftover, buffer);
		if (!temp)
			return (NULL);
		free(leftover);
		leftover = temp;
		nl_pos = find_newline(leftover);
		if (nl_pos != -1)
			break ;
	}
	if (bytes_read == -1)
		return (NULL);
	return (leftover);
}

static char	*extract_line(char *leftover)
{
	int		nl_pos;
	char	*line;

	nl_pos = find_newline(leftover);
	if (nl_pos < 0)
		return (ft_strdup(leftover));
	line = ft_substr(leftover, 0, nl_pos + 1);
	return (line);
}

static char	*update_leftover(char *leftover)
{
	int		nl_pos;
	char	*new_left;
	size_t	len;

	nl_pos = find_newline(leftover);
	if (nl_pos == -1)
	{
		free(leftover);
		return (NULL);
	}
	len = ft_strlen(leftover) - (nl_pos + 1);
	new_left = ft_substr(leftover, nl_pos + 1, len);
	free(leftover);
	return (new_left);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	leftover = read_until_newline(fd, leftover);
	if (!leftover)
		return (NULL);
	line = extract_line(leftover);
	leftover = update_leftover(leftover);
	return (line);
}

// #include <fcntl.h>

// int	main(void)
// {
// 	int fd = open("hi.txt", O_RDONLY);
// 	printf("%d\n", fd);
// 	char *line = get_next_line(fd);
// 	printf("%s\n", line);
// }