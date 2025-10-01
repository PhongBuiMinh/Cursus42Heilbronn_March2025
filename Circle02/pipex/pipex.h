/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:02:59 by fbui-min          #+#    #+#             */
/*   Updated: 2025/09/24 17:44:56 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"
# include "get_next_line.h"

typedef struct s_pipex {
	int	**pipes;
	int	n_cmds;
	int	here_doc;
	int	**here_pipe;
}		t_pipex;

void	free_strs(char **str);
void	free_pipes(int **pipes, int n_pipes);

void	fatal(char *error);
void	usage_exit(const char *mode);

char	*find_cmd_path(char *cmd, char **envp);
void	execute_command(char *argv, char **envp);

int		**allocate_pipes(int n_cmds);

#endif
