/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phong <phong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:23:29 by fbui-min          #+#    #+#             */
/*   Updated: 2025/04/20 17:23:15 by phong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// char	*extract_line(t_list **list)
// {
// 	char	*line;
// 	size_t	line_length;

// 	t_list	*traverse;

// 	traverse = list;
// 	while (traverse)
// 	{
		
// 	}
// }

bool	find_new_line(t_list *list)
{
	size_t	i;

	while (list)
	{
		i = 0;
		while (list->str[i])
		{
			if (list->str[i] == '\n')
				return (true);
			i++;
		}
		list = list->next;
	}
	return (false);
}

t_list	*append_to_list(t_list *head, char *str, int len)
{
	t_list	*new_node;
	t_list	*traverse;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	
	new_node->str = ft_strdup(str, len);
	new_node->length = len;
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
	int				bytes_read;

	buffer_list = NULL;
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			// free
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		buffer_list = append_to_list(buffer_list, buffer, bytes_read);
		if (find_new_line(buffer_list))
			break ;
	}
	return (buffer_list->str);
}

int	main(void)
{
	int	fd;

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

	char str[] = "Hello111\nWorld";
	char *newline = strchr(str, '\n');

	// Pointer arithmetic (offset calculation)
	size_t offset = newline - str;  
	printf("Offset: %zu\n", offset);

	return (0);
}
