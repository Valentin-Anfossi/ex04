#include <unistd.h>
#include <stdlib.h>

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
                if(last_fd != -1)
                    close(last_fd);
                return (1);
            }
        }
        if(last_fd != -1) // SI PAS 1ere on connecte last fd to stdin
        {

        }
        if(cmds[i+1]) // SI PAS derniere on connecte STDOUT to the pipe
        {

        }
        
        
        pid = fork();
        if(pid == -1)
            return (1);

        if(pid == 0)
        {
            execvp(cmds[i][0],cmds[i]);
            exit(1);
        }
        i ++;
    }
}