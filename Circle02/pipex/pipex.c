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

void	child_write_pipe(char **argv, char **envp, int *pipefd)
{
	int	filein;

	filein = open(argv[1], O_RDONLY);
	if (filein == -1)
		fatal("open filein");
	dup2(filein, 0);
	dup2(pipefd[1], 1);
	close(pipefd[0]);
	execute_command(argv[2], envp);
}

void	child_read_pipe(char **argv, char **envp, int *pipefd)
{
	int	fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fileout == -1)
		fatal("open fileout");
	dup2(pipefd[0], 0);
	dup2(fileout, 1);
	close(pipefd[1]);
	execute_command(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		usage_exit("std");
	if (pipe(pipefd) == -1)
		fatal("pipe");
	pid1 = fork();
	if (pid1 == 0)
		child_write_pipe(argv, envp, pipefd);
	pid2 = fork();
	if (pid2 == 0)
		child_read_pipe(argv, envp, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	while (wait(NULL) > 0)
		;
}

// sleep(60);
// ps aux | grep Z
// ps -el | grep defunct
