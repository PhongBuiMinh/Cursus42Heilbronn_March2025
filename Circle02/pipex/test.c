#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	pid_t pid = fork();
	if (pid == 0) {
		exit(0); // Child exits immediately
	} else {
		sleep(60); // Parent does not call wait()
	}
	// ps -eo pid,ppid,state,cmd | grep Z
	// ps -eo pid,ppid,state,cmd | grep <parent_pid>

	// (void)argc;
	// (void)argv;

	// int i = -1;
	// while (++i < 5)
	// 	printf("%s\n", envp[i]);
}

// 🧠 Key Rule
// If you only fork once, the parent must stay alive long enough to call waitpid() — and must not call execve() before doing so.
// Reaping = the parent calling wait() or waitpid() to collect the child’s exit status and remove it from the process table.

// int fd = open(const char *pathname, int flags, mode_t mode);
// pathname: Path to the file
// flags: File access mode (e.g., O_RDONLY, O_WRONLY, O_CREAT, etc.)
// mode: File permissions (used only when creating a file)
// The mode argument is only used when you include the O_CREAT flag

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

// void	child_process(char **argv, char **envp, int *pipefd)
// {
// 	int	filein;

// 	filein = open(argv[1], O_RDONLY);
// 	if (filein == -1)
// 	{
// 		perror("open filein");
// 		exit(1);
// 	}
// 	dup2(filein, 0);
// 	dup2(pipefd[1], 1);
// 	close(pipefd[0]);
// 	close(pipefd[1]);
// 	close(filein);
// 	execute_command(argv[2], envp);
// 	system(argv[2]); // in child
// }
