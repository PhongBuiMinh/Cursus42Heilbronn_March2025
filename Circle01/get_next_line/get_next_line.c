/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phong <phong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:23:29 by fbui-min          #+#    #+#             */
/*   Updated: 2025/04/24 07:40:37 by phong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// void	clean_list(t_list **list)
// {
// 	t_list	*last;
// 	char	*leftover;
// 	int		i;

// 	if (!list || !*list)
// 		return ;
// 	last = ft_lstlast(*list);
// 	if (!last || !last->str)
// 		return (ft_lstclear(list));
// 	i = 0;
// 	while (last->str[i] && last->str[i] != '\n')
// 		i++;
// 	if (last->str[i] != '\n')
// 		return (ft_lstclear(list));
// 	leftover = ft_strdup(&last->str[i + 1]);
// 	ft_lstclear(list);
// 	if (!leftover || !*leftover)
// 		return (free(leftover));
// 	*list = (t_list *)malloc(sizeof(t_list));
// 	if (!*list)
// 		return (*list = NULL, free(leftover));
// 	(*list)->str = leftover;
// 	(*list)->next = NULL;
// }

void	update_leftover(char *buffer)
{
	size_t	i;
	size_t	j;
	
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	j = 0;
	while (buffer[i])
		buffer[j++] = buffer[i++];
    while (j < BUFFER_SIZE)
        buffer[j++] = '\0';
}

char	*extract_line(t_list *lst)
{
	char	*line;
	size_t	line_length;
	int		i;
	size_t	j;

	line_length = calculate_line_length(lst);
	line = (char *)malloc((line_length + 1) * sizeof(char));
	if (!line)
		return (NULL);
	j = 0;
	while (lst && j < line_length)
	{
		i = -1;
		while (lst->str[++i] && j < line_length)
			line[j++] = lst->str[i];
		lst = lst->next;
	}
	line[line_length] = '\0';
	return (line);
}

bool	has_new_line(t_list *lst)
{
	if (!lst)
		return (false);
	while (lst)
	{
		if (ft_strchr(lst->str, '\n'))
			return (true);
		lst = lst->next;
	}
	return (false);
}

t_list	*append_to_list(t_list **head, char *buffer)
{
	t_list	*new_node;
	t_list	*last;
	char	*str_cpy;

	str_cpy = ft_strdup(buffer);
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node || !str_cpy)
		return (free(str_cpy), NULL);
	new_node->str = str_cpy;
	new_node->next = NULL;
	last = *head;
	if (!*head)
		*head = new_node;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
	// ft_lstlast(*head)->next = new_node;
	return (*head);
}

char	*get_next_line(int fd)
{
	t_list		*buffer_list;
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			bytes_read;

	buffer_list = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
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
	if (!line || !*line)
		return (free(line), NULL);
	ft_lstclear(&buffer_list);
	update_leftover(buffer);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*str;

// 	fd = open("test1.txt", O_RDONLY);
// 	str = get_next_line(fd);
// 	printf("Content1 in test1 file: %s\n", str);
// 	free(str);

// 	// str = get_next_line(fd);
// 	// printf("Content1 in test1 file: %s\n", str);
// 	// free(str);

// 	close(fd);

// 	// fd = open("test2.txt", O_RDONLY | O_CREAT);
// 	// close(fd);

// 	// printf("============================\n");
// 	// printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
// 	// printf("O_RDONLY = %d\n", O_RDONLY);
// 	// printf("O_WRONLY = %d\n", O_WRONLY);
// 	// printf("O_RDWR = %d\n", O_RDWR);
// 	// printf("O_CREAT = %d\n", O_CREAT);
// 	// printf("O_EXCL = %d\n", O_EXCL);

// 	// char str[] = "Hello111\nWorld";
// 	// char *newline = strchr(str, '\n');

// 	// Pointer arithmetic (offset calculation)
// 	// size_t offset = newline - str;  
// 	// printf("Offset: %zu\n", offset);

// 	return (0);
// }
