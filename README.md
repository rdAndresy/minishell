# minishell
Write a shell mimicking bash posix behavior in C

It breaks down the process into 4 steps: `launcher` → `lexer` → `parser` → `expander` → `checker` → `executor`

![image](https://github.com/rdAndresy/minishell/assets/98149837/a374e2ea-3523-423a-b9f4-a617618426f9)

# Resources

- [https://github.com/maiadegraaf/minishell](https://github.com/maiadegraaf/minishell)
- [https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)

# Usefull information
- Add the readline.supp file at the project directory's root to use with Valgrind
- Execute the program with the Valgrind extra flag --suppressions=readline.supp

# Authorized functions
1. `readline`: Reads a line from the terminal and returns it.
2. `rl_clear_history`: Clears the readline history.
3. `rl_on_new_line`: Tells readline that the cursor is on a new line.
4. `rl_replace_line`: Replaces the current line in the readline buffer.
5. `rl_redisplay`: Redraws the readline line.
6. `add_history`: Adds a line to the readline history.
7. `printf`: Prints formatted output to stdout.
8. `malloc`: Allocates memory.
9. `free`: Deallocates memory.
10. `write`: Writes data to a file descriptor.
11. `access`: Checks the accessibility of a file.
12. `open`: Opens a file.
13. `read`: Reads data from a file descriptor.
14. `close`: Closes a file descriptor.
15. `fork`: Creates a new process.
16. `wait`: Waits for a child process to stop or terminate.
17. `waitpid`: Waits for a specific child process to stop or terminate.
18. `wait3`: Waits for a child process to stop or terminate and also returns resource usage.
19. `wait4`: Waits for a specific child process to stop or terminate and also returns resource usage.
20. `signal`: Sets a function to handle a signal.
21. `sigaction`: Examines and changes a signal action.
22. `sigemptyset`: Initializes a signal set to empty.
23. `sigaddset`: Adds a signal to a signal set.
24. `kill`: Sends a signal to a process.
25. `exit`: Terminates the process.
26. `getcwd`: Gets the current working directory.
27. `chdir`: Changes the current working directory.
28. `stat`: Gets file status.
29. `ft_lstat`: Like `stat`, but if the file is a symbolic link, then it returns information about the link itself.
30. `fstat`: Like `stat`, but is used when the file descriptor is already open.
31. `unlink`: ft_deletes a name from the filesystem.
32. `execve`: Executes a file.
33. `dup`: Duplicates a file descriptor.
34. `dup2`: Duplicates a file descriptor to a specified file descriptor.
35. `pipe`: Creates a pipe.
36. `opendir`: Opens a directory.
37. `readdir`: Reads a directory.
38. `closedir`: Closes a directory.
39. `strerror`: Returns a string describing an error number.
40. `perror`: Prints a description of the last error encountered.
41. `isatty`: Tests whether a file descriptor refers to a terminal.
42. `ttyname`: Returns the name of the terminal.
43. `ttyslot`: Returns the index of the current user's terminal in the utmp file.
44. `ioctl`: Controls device.
45. `getenv`: Gets an environment variable.
46. `tcsetattr`: Sets the parameters associated with the terminal.
47. `tcgetattr`: Gets the parameters associated with the terminal.
48. `tgetent`: Loads the termcap entry for terminal.
49. `tgetflag`: Returns the boolean value of capability.
50. `tgetnum`: Returns the numeric value of capability.
51. `tgetstr`: Returns the string value of capability.
52. `tgoto`: Decodes a cursor motion string.
53. `tputs`: Applies padding information to a string and outputs it.
