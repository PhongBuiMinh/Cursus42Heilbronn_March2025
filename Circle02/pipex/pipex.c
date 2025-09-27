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

void	write_pipe(char **argv, char **envp, int *pipefd)
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

void	read_pipe(char **argv, char **envp, int *pipefd)
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
	pid_t	pid_r;
	pid_t	pid_w;

	if (argc != 5)
	{
		printf("Shell: < file1 cmd1 | cmd2 > file2\n");
		printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		exit(0);
	}
	if (pipe(pipefd) == -1)
		fatal("pipe");
	pid_w = fork();
	if (pid_w == 0)
		write_pipe(argv, envp, pipefd);
	pid_r = fork();
	if (pid_r == 0)
		read_pipe(argv, envp, pipefd);
	close(pidfd[0]);
	close(pidfd[1]);
	waitpid(pid_r, NULL, 0);
	waitpid(pid_w, NULL, 0);
}
