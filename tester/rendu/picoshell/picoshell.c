/* Assignment name:    picoshell
Expected files:        picoshell.c
Allowed functions:    close, fork, wait, exit, execvp, dup2, pipe
___

Write the following function:

int    picoshell(char *cmds[]);

The goal of this function is to execute a pipeline. It must execute each
commands [sic] of cmds and connect the output of one to the input of the
next command (just like a shell).

Cmds contains a null-terminated list of valid commands. Each rows [sic]
of cmds are an argv array directly usable for a call to execvp. The first
arguments [sic] of each command is the command name or path and can be passed
directly as the first argument of execvp.

If any error occur [sic], The function must return 1 (you must of course
close all the open fds before). otherwise the function must wait all child
processes and return 0. You will find in this directory a file main.c which
contain [sic] something to help you test your function.


Examples: 
./picoshell /bin/ls "|" /usr/bin/grep picoshell
picoshell
./picoshell echo 'squalala' "|" cat "|" sed 's/a/b/g'
squblblb/
*/


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int picoshell(char **cmds[])
{
	int     i;
	int     fd[2];
	int     old_fd = -1;
	pid_t child;

	i = 0;
	while (cmds[i])
	{
		if(cmds[i + 1]) // si une commande apres
			pipe(fd);
		child = fork();
		if (child == 0)
		{
			if (old_fd != -1) // si premiere commande
				dup2(old_fd, STDIN_FILENO);
			if (cmds[i +1]) //si pas la derniere commande
				dup2(fd[1], STDOUT_FILENO);
			//ferme tous fd du Child
			close(old_fd);
			close(fd[0]);
			close(fd[1]);
			execvp(cmds[i][0], cmds[i]);
			exit (1);
		}
		// ferme les fd parent
		if (old_fd != -1)
			close(old_fd);
		if (cmds[i + 1])
		{
			close(fd[1]);
			old_fd = fd[0];
		}
		i++;
	}
	return (0);
}

// int main()
// {
// 	 char *cmds0[] = {"echo", "youpi", NULL};
// 	 char *cmds1[] = {"/bin/ls", NULL};
// 	 char *cmds2[] = {"/usr/bin/grep", "picoshell", NULL};
//      char *cmds3[] = {"cat", "-e",NULL};
// 	// char *cmds3[] = {"wc","-c", NULL};
// 	// char *cmds4[] = {"cat", NULL};
// 	// char *cmds5[] = {"pwd", NULL};
// 	char **cmds[] = {cmds0, cmds1, cmds2, cmds3, NULL};

// 	picoshell(cmds);
// }