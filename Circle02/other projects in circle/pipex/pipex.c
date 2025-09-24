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

void	execute_command(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	// cmd = ft_split();
	path = find_cmd_path();
	execve(path, cmd, envp);
}

void	child_process(char **argv, char **envp int *pipefd)
{
	int	filein;

	filein = open(argv[1], O_RDONLY);
	if (filein == -1)
	{
		perror("open filein");
		exit(1);
	}
	dup2(filein, 0);
	dup2(pipefd[1], 1);
	close(pipefd[0]);
	close(pipefd[1]);
	close(filein);
	execute_command(argv[2], envp);
	// system(argv[2]); // in child
}
// int fd = open(const char *pathname, int flags, mode_t mode);
// pathname: Path to the file
// flags: File access mode (e.g., O_RDONLY, O_WRONLY, O_CREAT, etc.)
// mode: File permissions (used only when creating a file)
// The mode argument is only used when you include the O_CREAT flag

void	parent_process(char **argv, char **envp, int *pipefd)
{
	int	fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT, 0644);
	if (fileout == -1)
	{
		perror("open fileout");
		exit(1);
	}
	dup2(pipefd[0], 0);
	dup2(fileout, 1);
	close(pipefd[1]);
	close(pipefd[0]);
	close(fileout);
	execute_command(argv[3], envp);
	// system(argv[3]); // in parent
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	if (argc != 5)
	{
		printf("Usage: ./pipex < file1 cmd1 | cmd2 > file2");
		exit(0);
	}
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(0);
	}
	pid = fork();
	if (pid == 0)
		child_process(argv, envp, pipefd);
	else
	{
		waitpid(pid, NULL, 0);
		parent_process(argv, envp, pipefd);
	}
}

// waitpid 
// pid	The PID of the child process to wait for. Use -1 to wait for any child.
// status	Pointer to an int where the exit status will be stored. Use NULL if you don’t care.
// options	Flags to modify behavior. Use 0 for default blocking behavior.
// char *cmd_path = "/bin/ls";  // ✅ Tells the system what to run

// char	*cmd_args[] = {"ls", "-l", NULL};  // ✅ Tells it how to run it (with what args)

// char *custom_envp[] = {  // ✅ Tells it where and under what conditions to run it
// 	"PATH=/custom/bin:/usr/bin", // finding executables
// 	"LANG=en_US.UTF-8",
// 	"TERM=xterm-256color",
//	home user-specific paths
//	pwd current working directory
// 	NULL
// };

// The term key environment usually refers to the most important environment variables that influence how a program behaves when it's executed. These are the variables that define the system context—like where to find executables, how to format output, and what user or locale settings apply.
// 🧠 How It Works
// When a process (like your shell) launches another process (like ls), it passes its environment to the child.
// The child gets a copy of the environment—not a reference—so it can modify its own variables without affecting the parent.