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
			break;
		if (ft_strncmp(line, delimiter, len) == 0 && line[len] == '\n')
		{
			free(line);
			break;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

int	main(int argc, char **argv, char **envp)
{
	int		infile;
	int		outfile;
	int		prev_pipe_read;
	int		pipefd[2];
	int		i;
	pid_t	pid;

	if (argc < 5)
		usage_exit("Usage: ./pipex infile cmd1 cmd2 ... outfile");
	if (ft_memcmp(argv[1], "doc_here", 8) == 0)
	{
		prev_pipe_read = here_doc(argv[2]);
		i = 3;
		outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		infile = open(argv[1], O_RDONLY);
		if (infile == -1)
			fatal("open infile");
		prev_pipe_read = infile;
		i = 2;
		outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (outfile == -1)
		fatal("open outfile");
	while (i < argc - 2)
	{
		pipe(pipefd);
		pid = fork();
		if (pid == 0)
		{
			close(pipefd[0]);
			dup2(prev_pipe_read, 0);
			dup2(pipefd[1], 1);
			close(pipefd[1]);
			execute_command(argv[i], envp);
		}
		close(prev_pipe_read);
		close(pipefd[1]);
		prev_pipe_read = pipefd[0];
		i++;
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(prev_pipe_read, 0);
		dup2(outfile, 1);
		close(outfile);
		execute_command(argv[argc - 2], envp);
	}
	close(prev_pipe_read);
	close(outfile);
	while (wait(NULL) > 0)
		;
}
