#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#define ENTREE 1
#define SORTIE 0

int cmd(int fd[2])
{
    
}

int main(void)
{
    int pi[2];
    int lefd = 50;
    char *buffer = calloc(1,1000);

    pipe(pi);
    write(pi[ENTREE],"BA",3);
    //  pipe(pi);
    //write(STDOUT_FILENO,buffer,1000);
    dup2(pi[ENTREE],lefd); //FERME LEFD, LEFD EST ENVOYE VERS PIENTREE
    write(lefd,"BI",3);
    int pid = fork();
    if (pid == 0)
    {
        //dup2(pi[ENTREE], STDOUT_FILENO);
        write(pi[ENTREE],"BOU",4);
        exit(0);
    }

    wait(NULL);
    read(pi[SORTIE],buffer,1000);
    write(STDOUT_FILENO,buffer,1000);
}