#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>

int ft_popen(const char *file, char *const argv[], char type)
{
    int pi[2];
    pid_t child;
    

    pipe(pi);
    if(pi==0)
        return (-1);
    if(!file || !argv)
        return (-1);
    if(type != 'r' && type != 'w')
        return (-1);
    child = fork();
    if(child == -1)
    {
        close(pi[0]);
        close(pi[1]);
        return (-1);
    }
    if(child == 0)
    {
        if(type == 'r')
        {
            dup2(pi[1],STDOUT_FILENO);
            close(pi[0]);
            close(pi[1]);
        }
        else if(type == 'w')
        {
            dup2(pi[0],STDIN_FILENO);
            close(pi[0]);
            close(pi[1]);
        }
        execvp(file,argv);
        exit(1);
    }
    if(type == 'r')
    {
        close(pi[1]);
        return (pi[0]);
    }
    else if(type == 'w')
    {
        close(pi[0]);
        return(pi[1]);
    }
}

int main()
{
    int  fd;
    char line[256];

    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    while ((read(fd,line,256)))
        printf("%s",line);
    close(fd);
    return (0);
}