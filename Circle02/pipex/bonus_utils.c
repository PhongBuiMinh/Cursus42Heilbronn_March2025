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
