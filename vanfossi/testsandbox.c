#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <errno.h>
#include <signal.h>

void prout(int sig)
{
    printf("PROUT\n");
    sleep(3);
    (void)sig;

}

int main(void)
{
    int pid;
    int stat;
    
    struct sigaction sa;
    sa.sa_handler = prout;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask,SIGINT);
    sigaction(SIGALRM, &sa, NULL);

    pid = fork();
    if(pid == 0)
    {
        sleep(4);
        printf("JESUISLA\n");
        exit(1);
    }
    alarm(1);
    printf("errno = %d\n",errno);
    if(waitpid(pid,&stat,0) == -1)
    {
        if(errno == EINTR)
        {
            kill(pid,SIGKILL);
            waitpid(pid,NULL,0);
            printf("TIMEOUT ATTEINT\n");
            return (0);
        }
        return (-1);
    }
    if(WEXITSTATUS(stat) == 0)
    {
        printf("Nice function !\n");
    }
    if(WIFEXITED(stat) == 1)
    {
        printf("Bad : code = %d\n",WEXITSTATUS(stat));    
    }
    printf("errno = %d\n",errno);
}