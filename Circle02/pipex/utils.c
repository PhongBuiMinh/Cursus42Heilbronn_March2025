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

void	free_strs(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	usage_exit(const char *mode)
{
	if (!ft_memcmp(mode, "std", 3))
	{
		printf("Shell: < file1 cmd1 | cmd2 > file2\n");
		printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
	}
	else if (!ft_memcmp(mode, "mul", 3))
	{
		printf("Shell: < file1 cmd1 | cmd2 ... | cmdn > file2\n");
		printf("Usage: ./pipex file1 cmd1 cmd2 ... cmdn file2\n");
	}
	else if (!ft_memcmp(mode, "doc", 3))
	{
		printf("Shell: cmd << LIMITER | cmd1 >> file\n");
		printf("Usage: ./pipex here_doc LIMITER cmd cmd1 file\n");
	}
	exit(0);
}

void	fatal(char *error)
{
	perror(error);
	exit(1);
}

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
		fatal("cmd path");
	}
	execve(path, cmd, envp);
}
