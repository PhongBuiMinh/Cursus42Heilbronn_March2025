/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:23:29 by fbui-min          #+#    #+#             */
/*   Updated: 2025/04/25 22:26:39 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	update_leftover(char *buffer)
{
	size_t	i;
	size_t	j;

	if (!buffer || !*buffer)
		return ;
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	j = 0;
	while (buffer[i] && j < BUFFER_SIZE)
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
		i = 0;
		while (lst->str[i] && j < line_length)
			line[j++] = lst->str[i++];
		lst = lst->next;
	}
	line[line_length] = '\0';
	return (line);
}

void	append_to_list(t_list **head, char *buffer)
{
	t_list	*new_node;
	t_list	*last;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node || !buffer || !*buffer)
		return ;
	new_node->str = ft_strdup(buffer);
	if (!new_node->str)
		return (free(new_node->str), free(new_node));
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
}

char	*get_next_line(int fd)
{
	t_list		*buffer_list;
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			bytes_read;

	buffer_list = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0))
		return (buffer[0] = '\0', (NULL));
	if (*buffer)
		append_to_list(&buffer_list, buffer);
	while (!has_new_line(buffer_list))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		append_to_list(&buffer_list, buffer);
	}
	line = extract_line(buffer_list);
	ft_lstclear(&buffer_list);
	update_leftover(buffer);
	if (!line || !*line)
		return (free(line), NULL);
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
// 	str = get_next_line(fd);
// 	printf("Content1 in test1 file: %s\n", str);
// 	free(str);
// 	str = get_next_line(fd);
// 	printf("Content1 in test1 file: %s\n", str);
// 	free(str);
// 	str = get_next_line(fd);
// 	printf("Content1 in test1 file: %s\n", str);
// 	free(str);
// 	str = get_next_line(fd);
// 	printf("Content1 in test1 file: %s\n", str);
// 	free(str);
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
