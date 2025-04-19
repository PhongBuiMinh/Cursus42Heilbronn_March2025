/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:23:29 by fbui-min          #+#    #+#             */
/*   Updated: 2025/04/19 18:53:12 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

bool	find_next_line(t_list *list)
{
	t_list	*traverse;
	size_t	i;

	traverse = list;
	while (traverse)
	{
		i = 0;
		while (traverse->str[i])
		{
			if (traverse->str[i] == '\n')
				return (true);
			i++;
		}
		traverse = traverse->next;
	}
	return (false);
}

t_list	*append_to_list(t_list *head, char *str)
{
	t_list	*new_node;
	t_list	*traverse;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->str = ft_strdup(str);
	new_node->next = NULL;

	if (head == NULL)
		return (new_node);
	traverse = head;
	while (traverse->next)
		traverse = traverse->next;
	traverse->next = new_node;
	return (head);
}

char	*get_next_line(int fd)
{
	static t_list	*buffer_list;
	char			buffer[BUFFER_SIZE + 1];
	size_t			bytes_read;

	buffer_list = NULL;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		buffer_list = append_to_list(buffer_list, buffer);
		printf("Check\n");
		if (find_next_line(buffer_list))
		{
			printf("Found\n");
			break ;
		}

		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (buffer_list->str);
}

int	main(void)
{
	int	fd;
	int	i;

	i = 0;
	fd = open("test1.txt", O_RDONLY);
	printf("Content in test1 file: %s\n", get_next_line(fd));
	close(fd);

	fd = open("test2.txt", O_RDONLY | O_CREAT);
	close(fd);

	// printf("============================\n");
	// printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
	// printf("O_RDONLY = %d\n", O_RDONLY);
	// printf("O_WRONLY = %d\n", O_WRONLY);
	// printf("O_RDWR = %d\n", O_RDWR);
	// printf("O_CREAT = %d\n", O_CREAT);
	// printf("O_EXCL = %d\n", O_EXCL);

	return (0);
}
