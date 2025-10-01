/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:02:59 by fbui-min          #+#    #+#             */
/*   Updated: 2025/10/01 15:58:50 by fbui-min         ###   ########.fr       */
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

// typedef struct s_file {
// 	int	infile;
// 	int	outfile;
// }	t_file;

void	init_in_out(int argc, char **argv, int *file);
int		get_start_index(char *argv);
void	free_strs(char **str);
void	fatal(char *error);
void	usage_exit(const char *mode);

char	*find_cmd_path(char *cmd, char **envp);
void	execute_command(char *argv, char **envp);

#endif
