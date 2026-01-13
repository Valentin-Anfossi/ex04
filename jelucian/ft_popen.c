/*
Allowed functions: pipe, fork, dup2, execvp, close, exit
--------------------------------------------------------------------------------------
Write the following function:

int ft_popen(const char *file, char *const argv[], char type);

The function must launch the executable file with the arguments argv (using execvp).
If type is 'r' the function must return a file descriptor connected to the output of the command.
If type is 'w' the function must return a file descriptor connected to the input of the command.
In case of error or invalid parameter the function must return -1.

For example, the function could be used like that:

int main()
{
    int  fd;
    char *line;

    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    while ((line = get_next_line(fd)))
        ft_putstr(line);
    return (0);
}


int	main() {
	int	fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
	dup2(fd, 0);
	fd = ft_popen("grep", (char *const []){"grep", "c", NULL}, 'r');
	char	*line;
	while ((line = get_next_line(fd)))
		printf("%s", line);
}


Hints:
Do not leak file descriptors!
This exercise is inspired by the libc's popen().*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"



int ft_popen(const char *file, char *const argv[], char type)
{
    int fd[2];
  //  int fd_open;
    pid_t   pid;
    
    if(!file || !argv || (type != 'r' && type != 'w'))
        return (-1);
    
    if(pipe(fd) == -1)
        return (-1);
    
    pid = fork();
    if(pid == -1)
    {
        close(fd[0]);
        close(fd[1]);
        return (-1);
    }
    if (pid == 0)
    {

        if (type == 'r')
        {
            if(dup2(fd[1], STDOUT_FILENO) == -1)
            {
                printf("we gonna die !\n");
                close(fd[0]);
                close(fd[1]);
                exit(1);
            }
        }
        if (type == 'w')
        {

            if(dup2(fd[0], STDIN_FILENO) == - 1)
            {
                close(fd[0]);
                close(fd[1]);
                exit(1);
            }
            
        }
        close(fd[1]);
        close(fd[0]);
        execvp(file, argv);
        exit(-1);
    }
    if (type == 'w')
    {
        close(fd[0]);
        return (fd[1]);
    }
    else if (type == 'r')
    {
        close(fd[1]);
        return (fd[0]);
    }
    else
    {
        close(fd[0]);
        close(fd[1]);
        return (1);
    }
}

int	main() {
    int save_out;
    int save_out2;
    int save_out3;

    save_out = dup(STDOUT_FILENO);
    save_out2 = dup(STDOUT_FILENO);
    save_out3 = dup(STDOUT_FILENO);
    close(STDOUT_FILENO);
    printf("%d  %p %p %p\n",STDOUT_FILENO, save_out, save_out2, save_out3);
    dup2(save_out,STDOUT_FILENO);
	int	fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
	dup2(fd, STDIN_FILENO);
    close(fd);
	fd = ft_popen("grep", (char *const []){"grep", "c", NULL}, 'r');
    char	*line;
    line = calloc(1,1000);
	read(fd,line,900);
    printf("%s",line);
	// while ((line = get_next_line(fd)))
		// printf("%s", line);
    close(fd);
}