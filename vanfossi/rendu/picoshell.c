#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int picoshell(char **cmds[])
{
    int pi[2];
    int pid;
    int last_fd = -1;
    int i = 0;
    
    while(cmds[i])
    {
        if(cmds[i + 1])
        {
            if(pipe(pi) == -1)
            {
                return (1);
            }
        }
        pid = fork();

        if(pid == -1)
        {
            if(cmds[i+1])
            {
                close(pi[0]);
                close(pi[1]);
            }
            return (1);
        }

        if(pid == 0)
        {
            if(cmds[i+1])
            {
                dup2(pi[1],STDOUT_FILENO);
                close(pi[0]);
                close(pi[1]);
            }
            if(last_fd != -1)
            {
                dup2(last_fd,STDIN_FILENO);
                close(last_fd);
            }
            execvp(cmds[i][0],cmds[i]);
            exit(1);
        }
        if(last_fd != -1)
            close(last_fd);
        if(cmds[i+1])
        {
            last_fd = pi[0];
            close(pi[1]);
        }

        i ++;
    }

    int statloc;
    int laststat = 0;
    while(wait(&statloc) != -1)
    {
        if(statloc != 0)
            laststat = 1;
    }
    return (laststat);
}