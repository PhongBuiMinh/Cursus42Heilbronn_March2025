#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	pid_t pid = fork();
	if (pid == 0) {
		exit(0); // Child exits immediately
	} else {
		sleep(60); // Parent does not call wait()
	}
	// system(argv[2]); // in child
	// ps -eo pid,ppid,state,cmd | grep Z
	// ps -eo pid,ppid,state,cmd | grep <parent_pid>
	// ps aux | grep Z
	// ps -el | grep defunct

	// (void)argc;
	// (void)argv;

	// int i = -1;
	// while (++i < 5)
	// 	printf("%s\n", envp[i]);
}

// A pipe end is only actually closed when ALL processes that have it open call close() on it.
// Reaping = the parent calling wait() or waitpid() to collect the child’s exit status and remove it from the process table.
// Parent closing doesn't affect children, but it can destroy pipes if you close them before all children that need them are forked.
// Close in parent loop: Children are messy, but parent cleans up systematically
// Close in children: Children are clean from the start

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
