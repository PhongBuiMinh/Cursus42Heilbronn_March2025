🔄 What dup2() does:
dup2(old_fd, new_fd) makes new_fd point to the same file/pipe as old_fd

Before any dup2() calls:
File Descriptors:
0 (stdin)  → keyboard
1 (stdout) → terminal  
2 (stderr) → terminal
3 (filein) → input file
4 (fd[1])  → pipe write end
5 (fd[0])  → pipe read end

///// WRITER
After dup2(fd[1], 1):
dup2(fd[1], 1);  // Make stdout point to pipe write end
File Descriptors:
0 (stdin)  → keyboard
1 (stdout) → pipe write end  ⬅️ CHANGED! (was terminal)
2 (stderr) → terminal
3 (filein) → input file
4 (fd[1])  → pipe write end (redundant copy)
5 (fd[0])  → pipe read end
Effect: Anything written to stdout (fd 1) now goes into the pipe instead of the terminal.

After dup2(filein, 0):
dup2(filein, 0);  // Make stdin point to input file
File Descriptors:
0 (stdin)  → input file      ⬅️ CHANGED! (was keyboard)
1 (stdout) → pipe write end
2 (stderr) → terminal
3 (filein) → input file (redundant copy)
4 (fd[1])  → pipe write end (redundant copy)
5 (fd[0])  → pipe read end
Effect: Anything read from stdin (fd 0) now comes from the file instead of the keyboard.

File Descriptors:
0 (stdin)  → input file
1 (stdout) → pipe write end
2 (stderr) → terminal
3 (filein) → input file (redundant)
4 (fd[1])  → pipe write end (redundant)
5 (fd[0])  → CLOSED ✅

Result:
cmd1 now has:
- stdin (fd 0)  → reading from input file
- stdout (fd 1) → writing to pipe
So: cmd1 reads from file, processes data, writes results to pipe



/////// READER
Before any dup2() calls:
File Descriptors:
0 (stdin)  → keyboard
1 (stdout) → terminal  
2 (stderr) → terminal
3 (fileout) → output file
4 (fd[0])  → pipe read end
5 (fd[1])  → pipe write end

File Descriptors:
0 (stdin)  → pipe read end
1 (stdout) → output file
2 (stderr) → terminal
3 (fileout) → CLOSED ✅
4 (fd[0])  → CLOSED ✅
5 (fd[1])  → CLOSED ✅



filein -> process1 -> pipe -> process2 -> fileout


📋 What waitpid() does:
Waits for the first child process (cmd1) to finish
Prevents zombie processes
Ensures proper execution order
Parent process:
├── fork() → create child1 (cmd1)
├── waitpid() → WAIT HERE for child1 to finish
└── then run parent (cmd2) ✅ SEQUENTIAL
Result: cmd1 finishes completely before cmd2 starts

A "zombie process" is a process that has finished executing but still has an entry in the process table. Here's why it's called that:
💀 Why "zombie"?
The analogy:
Living process: Running normally
Dead process: Finished execution
Zombie process: "Dead" but still "walking around" in the process table

✅ 1. Command Execution (execve)
Right now, your child_process() and parent_process() functions prepare the redirections but don’t actually execute the commands. You need to call execve() or execvp() to run argv[2] and argv[3] respectively.

You’ll need to split argv[2] and argv[3] into command + arguments, which can be done with a custom ft_split() or strtok().

✅ 4. Command Parsing
Right now, you're passing argv[2] and argv[3] directly. You’ll need to parse them into arrays for execvp() or execve().

✅ 5. Environment Variables
If you use execve(), you’ll need to pass envp from main():

✅ 6. Command Path Resolution
If you're using execve(), you must resolve the full path of the command (e.g., /bin/ls). You can search $PATH manually or use execvp() which does it for you.

perror() -> open(), fork(), pipe()

🔍 Why This Matters
When you run a command like ls in the shell, the shell looks through directories listed in $PATH (like /bin, /usr/bin, etc.) to find ls. But execve() doesn’t do that—it expects you to give it something like:

c
execve("/bin/ls", args, envp);
If you just pass "ls" as the path:

c
execve("ls", args, envp); // ❌ will fail unless "ls" is in the current directory

Parameter	Role
cmd_path	Tells the system what to run
cmd_args	Tells it how to run it (with what args)
envp	Tells it where and under what conditions to run it


Parameter	Value	Role
cmd_path	"/bin/ls"	Tells the system to run the ls executable
cmd_args	{"ls", "-l", NULL}	Passes arguments to ls, just like in a shell
envp	Custom environment array	Controls behavior like language, terminal type, and search paths

Ah, now we're bridging the gap between system-level environment variables and developer tools like .env files. Great connection!

🧾 What Is a .env File?
A .env file is a text file used in development to define environment variables in a simple KEY=value format. It's not part of the operating system, but many frameworks and tools (like Node.js, Python, Docker, etc.) use it to simulate or inject environment variables into your app.

Path	Purpose
/usr/local/bin	For user-installed software (e.g., custom tools, compiled binaries)
/usr/bin	For standard system binaries installed by the OS or package manager
/bin	For essential system commands needed for basic functionality (e.g., ls, cp, mv)