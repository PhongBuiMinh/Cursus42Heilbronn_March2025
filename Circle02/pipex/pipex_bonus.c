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

void	child_chain(char *argv, char **envp, int *pipefd, int inputfd)
{
	close(pipefd[0]);
	dup2(inputfd, 0);
	dup2(pipefd[1], 1);
	close(inputfd);
	close(pipefd[1]);
	execute_command(argv, envp);
}

void	child_last(char *argv, char **envp, int *fd)
{
	dup2(fd[2], 0);
	dup2(fd[1], 1);
	close(fd[1]);
	execute_command(argv, envp);
}

static void	process_commands(int argc, char **argv, char **envp, int *fd)
{
	int		pipefd[2];
	int		i;
	pid_t	pid;

	i = get_start_index(argv[1]);
	while (i < argc - 2)
	{
		pipe(pipefd);
		pid = fork();
		if (pid == 0)
			child_chain(argv[i], envp, pipefd, fd[2]);
		close(fd[2]);
		close(pipefd[1]);
		fd[2] = pipefd[0];
		i++;
	}
	pid = fork();
	if (pid == 0)
		child_last(argv[argc - 2], envp, fd);
	close(fd[2]);
	close(fd[1]);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[3];

	if (argc < 5)
		usage_exit("Usage: ./pipex infile cmd1 cmd2 ... outfile");
	init_in_out(argc, argv, fd);
	fd[2] = fd[0];
	process_commands(argc, argv, envp, fd);
	while (wait(NULL) > 0)
		;
}
