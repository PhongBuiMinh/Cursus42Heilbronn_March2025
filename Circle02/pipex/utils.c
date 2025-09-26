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

void	fatal(char type)
{
	if (type == 'i')
		perror("open filein");
	else if (type == 'o')
		perror("open fileout");
	else if (type == 'p')
		perror("pipe");
	else if (type == 'c')
		perror("cmd path");
	exit(1);
}

// void	fatal(char *error)
// {
// 	perror("%s", error);
// 	exit(1);
// }
