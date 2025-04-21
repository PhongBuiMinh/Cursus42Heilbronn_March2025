/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phong <phong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:23:29 by fbui-min          #+#    #+#             */
/*   Updated: 2025/04/21 14:14:21 by phong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*create_left_overs(t_list *list)
{
	size_t	i;
	char	*new_str;

	while (list)
	{
		i = -1;
		while (list->str[++i])
		{
			if (list->str[i] == '\n')
				break ;
		}
		list = list->next;
	}
	new_str = ft_strchr(list->str, '\n');
	return (new_str);
}

size_t	calculate_line_length(t_list *list)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (list)
	{
		i = -1;
		while (list->str[++i] && list->str[i] != '\n');
		len += i;
		if (list->str[i] == '\n')
		{
			len++;
			break ;
		}
		list = list->next;
	}
	// printf("line length = %zu\n", len);
	return (len);
}	

char	*extract_line(t_list *list)
{
	char	*line;
	size_t	line_length;
	size_t	i;
	size_t	j;

	line_length = calculate_line_length(list);
	line = malloc((line_length + 1) * sizeof(char));
	if (!line)
		return (NULL);
	j = 0;
	while (list)
	{
		i = -1;
		while (list->str[++i] && j < line_length)
			line[j++] = list->str[i];
		list = list->next;
	}
	line[line_length] = '\0';
	return (line);
}

bool	find_new_line(t_list *list)
{
	size_t	i;

	while (list)
	{
		i = -1;
		while (list->str[++i])
		{
			if (list->str[i] == '\n')
				return (true);
		}
		list = list->next;
	}
	return (false);
}

t_list *append_to_list(t_list **head, char *str)
{
	t_list	*new_node;
	t_list	*current;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);

	new_node->str = ft_strdup(str);
	if (!new_node->str)
		return (free(str), NULL);
	new_node->next = NULL;

	if (*head == NULL)
		return (*head = new_node);
	
	current = *head;
	while (current->next)
		current = current->next;

	current->next = new_node;
	return (*head);
}

char	*get_next_line(int fd)
{
	static t_list	*buffer_list;
	char			buffer[BUFFER_SIZE + 1];
	int				bytes_read;

	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!append_to_list(&buffer_list, buffer))
			return (NULL);
		if (find_new_line(buffer_list))
			break ;
	}
	create_left_overs(buffer_list);
	return (extract_line(buffer_list));
}

int	main(void)
{
	int	fd;

	fd = open("test1.txt", O_RDONLY);
	printf("Content in test1 file: %s\n", get_next_line(fd));
	close(fd);

	// fd = open("test2.txt", O_RDONLY | O_CREAT);
	// close(fd);

	// printf("============================\n");
	// printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
	// printf("O_RDONLY = %d\n", O_RDONLY);
	// printf("O_WRONLY = %d\n", O_WRONLY);
	// printf("O_RDWR = %d\n", O_RDWR);
	// printf("O_CREAT = %d\n", O_CREAT);
	// printf("O_EXCL = %d\n", O_EXCL);

	// char str[] = "Hello111\nWorld";
	// char *newline = strchr(str, '\n');

	// Pointer arithmetic (offset calculation)
	// size_t offset = newline - str;  
	// printf("Offset: %zu\n", offset);

	return (0);
}
