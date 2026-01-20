#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int sandbox(void (*f)(void), unsigned int timeout, bool verbose);

void alarm_handler(int sig)
{
    (void) sig;
    return ;
}

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
    int pid = -1;
    struct sigaction sa;
    
    sa.sa_handler = alarm_handler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGALRM,&sa,NULL);
    pid = fork();
    if(pid == -1)
        return (-1);
    if(pid == 0)
    {
        f();
        exit(0);
    }
    alarm(timeout);

    int status = -1;
    if(wait(&status) == -1) // Alarm closes wait and returns -1
    {
        if(errno == EINTR) // check si on a ete interrup par alarm
        {
            kill(pid, SIGKILL);
            wait(&status);
            if(verbose)
            {
                printf("Bad function: timed out after %d seconds\n",timeout);
                return (0);
            }
        }
        return(-1); // Si wait a bug sans etre interrup par alarm() on retourne -1
    }
    if(WIFEXITED(status))
    {
        if(status == 0)
        {
            if(verbose)
                printf("Nice function!\n");
            return (1);
        }
        else
        {
            if(verbose)
                printf("Bad function: exited with code %d\n", WEXITSTATUS(status));
            return (0);
        }
    }
    if(WIFSIGNALED(status))
    {
        if(verbose)
            printf("Bad function: %s\n",strsignal(WTERMSIG(status)));
        return (0);
    }
    return (-1);
}
