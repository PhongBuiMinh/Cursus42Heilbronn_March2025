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

char	*find_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (envp[i] && ft_memcmp(envp[i], "PATH=", 5))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, cmd);
		if (!access(path, F_OK))
			break ;
		free(path);
		i++;
	}
	free_strs(paths);
	return (path);
}

void	execute_command(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	path = find_cmd_path(cmd[0], envp);
	if (!path)
	{
		free_strs(cmd);
		fatal('c');
	}
	execve(path, cmd, envp);
}

void	child_process(char **argv, char **envp, int *pipefd)
{
	int	filein;

	filein = open(argv[1], O_RDONLY);
	if (filein == -1)
		fatal('i');
	dup2(filein, 0);
	dup2(pipefd[1], 1);
	close(pipefd[0]);
	close(pipefd[1]);
	close(filein);
	execute_command(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *pipefd)
{
	int	fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fileout == -1)
		fatal('o');
	dup2(pipefd[0], 0);
	dup2(fileout, 1);
	close(pipefd[1]);
	close(pipefd[0]);
	close(fileout);
	execute_command(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	if (argc != 5)
	{
		printf("Shell: < file1 cmd1 | cmd2 > file2");
		printf("Usage: ./pipex file1 cmd1 cmd2 file2");
		exit(0);
	}
	if (pipe(pipefd) == -1)
		fatal('p');
	pid = fork();
	if (pid == 0)
		child_process(argv, envp, pipefd);
	else
	{
		waitpid(pid, NULL, 0);
		parent_process(argv, envp, pipefd);
	}
}
