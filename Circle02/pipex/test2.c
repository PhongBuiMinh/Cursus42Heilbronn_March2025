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

typedef struct s_pipex {
	int	**pipes;
	int	n_cmds;
	int	here_doc;
	int	**here_pipe;
}	t_pipex;

void	free_pipes(int **pipes, int n_pipes)
{
	int	i;

	i = -1;
	while (++i < n_pipes)
		free(pipes[i]);
	free(pipes);
}

int	**allocate_pipes(int n_cmds)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * (n_cmds - 1));
	if (!pipes)
		fatal("malloc pipes");
	i = 0;
	while (i < n_cmds - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			fatal("malloc pipe fd");
		if (pipe(pipes[i]) == -1)
			fatal("pipe");
		i++;
	}
	return (pipes);
}

// void	here_doc(char *limiter, int *here_pipe)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		write(1, "heredoc> ", 9);
// 		line = get_next_line(0);
// 		if (!line || ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
// 		{
// 			free(line);
// 			break;
// 		}
// 		write(here_pipe[1], line, ft_strlen(line));
// 		free(line);
// 	}
// }

// void	child_input(t_pipex *pipex, char **argv, char **envp)
// {
// 	int	filein;

// 	if (pipex->here_doc)
// 	{
// 		dup2(pipex->here_pipe[0], 0);
// 		close(pipex->here_pipe[0]);
// 	}
// 	else
// 	{
// 		filein = open(argv[1], O_RDONLY);
// 		if (filein == -1)
// 			fatal("open infile");
// 		dup2(filein, 0);
// 		close(filein);
// 	}
// 	dup2(pipex->pipes[0][1], 1);
// 	close(pipex->pipes[0][0]);
// 	close(pipex->pipes[0][1]);
// 	execute_command(argv[2], envp);
// }

// void	child_mid(t_pipex *pipex, char **argv, char **envp, int i)
// {
// 	dup2(pipex->pipes[i - 1][0], 0);
// 	dup2(pipex->pipes[i][1], 1);
// 	close(pipex->pipes[i][0]);
// 	close(pipex->pipes[i - 1][1]);
// 	close(pipex->pipes[i - 1][0]);
// 	close(pipex->pipes[i][1]);
// 	execute_command(argv[i + 2], envp);
// }

// void	child_output(t_pipex *pipex, char **argv, char **envp)
// {
// 	int	fileout;

// 	fileout = open(argv[pipex->n_cmds + 1],
// 		O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fileout == -1)
// 		fatal("open fileout");
// 	dup2(pipex->pipes[pipex->n_cmds - 2][0], 0);
// 	dup2(fileout, 1);
// 	close(pipex->pipes[pipex->n_cmds - 2][1]);
// 	close(fileout);
// 	close(pipex->pipes[pipex->n_cmds - 2][0]);
// 	execute_command(argv[pipex->n_cmds + 1], envp);
// }

// void	parent_process(t_pipex *pipex)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < pipex->n_cmds - 1)
// 	{
// 		close(pipex->pipes[i][0]);
// 		close(pipex->pipes[i][1]);
// 	}
// 	while (wait(NULL) > 0)
// 		;
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_pipex	pipex;
// 	pid_t	pid;
// 	int		i;

// 	if (argc < 5)
// 	{
// 		usage_exit("mul");
// 		usage_exit("doc");
// 	}
// 	pipex.n_cmds = argc - 3;
// 	if (ft_memcmp(argv[1], "here_doc", 8) == 0)
// 	{
// 		pipex.here_doc = 1;
// 		pipex.n_cmds--;
// 	}
// 	pipex.pipes = allocate_pipes(pipex.n_cmds);
// 	if (pipex.here_doc)
// 	{
// 		if (pipe(pipex.here_pipe) == -1)
// 			fatal("pipe here_doc");
// 		here_doc(argv[2], pipex.here_pipe);
// 	}
// 	i = -1;
// 	while (++i < pipex.n_cmds)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			if (i == 0)
// 				child_input(&pipex, argv, envp);
// 			else if (i == pipex.n_cmds - 1)
// 				child_output(pipex, argv, envp);
// 			else
// 				child_mid(pipex, argv, envp, i);
// 		}
// 	}
// 	parent_process(&pipex);
// 	free_pipes(pipex.pipes, pipex.n_cmds - 1);
// }
