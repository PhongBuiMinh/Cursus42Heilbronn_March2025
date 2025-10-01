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

void	init_in_out(int argc, char **argv, int *file)
{
	if (ft_memcmp(argv[1], "doc_here", 8) == 0)
	{
		file[0] = here_doc(argv[2]);
		file[1] = open(argv[argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		file[0] = open(argv[1], O_RDONLY);
		if (file[0] == -1)
			fatal("open infile");
		file[1] = open(argv[argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (file[1] == -1)
		fatal("open outfile");
}

int	get_start_index(char *argv)
{
	if (ft_memcmp(argv, "doc_here", 8) == 0)
		return (3);
	return (2);
}

void	free_strs(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	fatal(char *error)
{
	perror(error);
	exit(1);
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
