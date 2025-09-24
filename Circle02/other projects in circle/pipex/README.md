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
File Descriptors:
0 (stdin)  → pipe read end
1 (stdout) → output file
2 (stderr) → terminal
3 (fileout) → CLOSED ✅
4 (fd[1])  → CLOSED ✅
5 (fd[0])  → CLOSED ✅



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