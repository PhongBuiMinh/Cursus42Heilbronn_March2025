/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:23:29 by fbui-min          #+#    #+#             */
/*   Updated: 2025/04/23 20:45:02 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clean_list(t_list **list)
{
	t_list	*last;
	char	*leftover;
	int		i;

	if (!list || !*list)
		return ;
	last = ft_lstlast(*list);
	if (!last || !last->str)
		return (ft_lstclear(list));
	i = 0;
	while (last->str[i] && last->str[i] != '\n')
		i++;
	if (last->str[i] != '\n')
		return (ft_lstclear(list));
	leftover = ft_strdup(&last->str[i + 1]);
	ft_lstclear(list);
	if (!leftover || !*leftover)
		return (free(leftover));
	*list = (t_list *)malloc(sizeof(t_list));
	if (!*list)
		return (*list = NULL, free(leftover));
	(*list)->str = leftover;
	(*list)->next = NULL;
}

char	*extract_line(t_list *list)
{
	char	*line;
	size_t	line_length;
	int		i;
	size_t	j;

	line_length = calculate_line_length(list);
	line = (char *)malloc((line_length + 1) * sizeof(char));
	if (!line)
		return (NULL);
	j = 0;
	while (list && j < line_length)
	{
		i = -1;
		while (list->str[++i] && j < line_length)
			line[j++] = list->str[i];
		list = list->next;
	}
	line[line_length] = '\0';
	return (line);
}

bool	has_new_line(t_list *list)
{
	if (!list)
		return (false);
	while (list)
	{
		if (ft_strchr(list->str, '\n'))
			return (true);
		list = list->next;
	}
	return (false);
}

t_list	*append_to_list(t_list **head, char *str)
{
	t_list	*new_node;
	char	*str_cpy;

	str_cpy = ft_strdup(str);
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node || !str_cpy)
		return (free(str_cpy), NULL);
	new_node->str = str_cpy;
	new_node->next = NULL;
	if (!*head)
		*head = new_node;
	else
		ft_lstlast(*head)->next = new_node;
	return (*head);
}

char	*get_next_line(int fd)
{
	static t_list	*buffer_list;
	char			buffer[BUFFER_SIZE + 1];
	char			*line;
	int				bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!has_new_line(buffer_list))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (ft_lstclear(&buffer_list), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!append_to_list(&buffer_list, buffer))
			return (ft_lstclear(&buffer_list), NULL);
	}
	line = extract_line(buffer_list);
	clean_list(&buffer_list);
	if (!line || !*line)
		return (free(line), NULL);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("test1.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("Content1 in test1 file: %s\n", str);
	free(str);

	// str = get_next_line(fd);
	// printf("Content1 in test1 file: %s\n", str);
	// free(str);
	
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
