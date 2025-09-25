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

int	main(int argc, char **argv, char **envp)
{
	return (0);
}


// ./pipex file1 cmd1 cmd2 cmd3 ... cmdN file2
// < file1 cmd1 | cmd2 | cmd3 | ... | cmdN > file2

// ./pipex here_doc LIMITER cmd1 cmd2 ... cmdN file
// cmd << LIMITER | cmd1 | ... >> file
