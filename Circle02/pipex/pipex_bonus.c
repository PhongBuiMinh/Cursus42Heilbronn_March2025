/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:41:16 by fbui-min          #+#    #+#             */
/*   Updated: 2025/09/24 19:07:42 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	here_doc(char *delimiter)
{
	int		pipefd[2];
	char	*line;
	int		len;

	len = ft_strlen(delimiter);
	pipe(pipefd);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, len) == 0 && line[len] == '\n')
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

void	child_chain(char *argv, char **envp, int *pipefd, int prev_pipe_read)
{
	close(pipefd[0]);
	dup2(prev_pipe_read, 0);
	dup2(pipefd[1], 1);
	close(pipefd[1]);
	execute_command(argv, envp);
}

void	child_last(char *argv, char **envp, int *file)
{
	dup2(file[0], 0);
	dup2(file[1], 1);
	close(file[1]);
	execute_command(argv, envp);
}

void	init_in_out(int argc, char **argv, int *file)
{
	if (ft_memcmp(argv[1], "doc_here", 8) == 0)
	{
		file[0] = here_doc(argv[2]);
		file[1] = open(argv[argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		file[0] = open(argv[1], O_RDONLY);
		if (file[0] == -1)
			fatal("open infile");
		file[1] = open(argv[argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (file[1] == -1)
		fatal("open outfile");
}

int	main(int argc, char **argv, char **envp)
{
	int		file[2];
	int		pipefd[2];
	int		i;
	pid_t	pid;

	if (argc < 5)
		usage_exit("Usage: ./pipex infile cmd1 cmd2 ... outfile");
	printf("before\nfile in: %d, file out: %d\n", file[0], file[1]);
	init_in_out(argc, argv, file);
	printf("after\nfile in: %d, file out: %d\n", file[0], file[1]);
	i = 2;
	if (ft_memcmp(argv[1], "doc_here", 8) == 0)
		i++;
	while (i < argc - 2)
	{
		pipe(pipefd);
		pid = fork();
		if (pid == 0)
			child_chain(argv[i], envp, pipefd, file[0]);
		close(file[0]);
		close(pipefd[1]);
		file[0] = pipefd[0];
		i++;
	}
	pid = fork();
	if (pid == 0)
		child_last(argv[argc - 2], envp, file);
	close(file[0]);
	// close(outfile);
	while (wait(NULL) > 0)
		;
}
