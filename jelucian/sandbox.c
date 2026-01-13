// Assignment name  : sandbox
// Expected files   : sandbox.c
// Allowed functions: fork, waitpid, exit, alarm, sigaction, kill, printf, strsignal,
// errno, sigaddset, sigemptyset, sigfillset, sigdelset, sigismember
// --------------------------------------------------------------------------------------

// Write the following function:

// #include <stdbool.h>
// int sandbox(void (*f)(void), unsigned int timeout, bool verbose);

// This function must test if the function f is a nice function or a bad function, you
// will return 1 if f is nice, 0 if f is bad or -1 in case of an error in your function.

// A function is considered bad if it is terminated or stopped by a signal (segfault, abort...),
// if it exit with any other exit code than 0 or if it times out.

// If verbose is true, you must write the appropriate message among the following:
// "Nice function!\n"
// "Bad function: exited with code <exit_code>\n"
// "Bad function: <signal description>\n"
// "Bad function: timed out after <timeout> seconds\n"

// You must not leak processes (even in zombie state, this will be checked using wait).

// We will test your code with very bad functions.
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

void alarm_handler(int sig)
{
    (void)sig;
}

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
    __pid_t pid;
    struct sigaction sa;
    int stat;
    sa.sa_handler = alarm_handler;
    sigaction(SIGALRM, &sa, NULL);

    pid = fork();
    if (pid == 0)
    {
        f();
        exit(1);
    }
    alarm(timeout);
    
    if (waitpid(pid, &stat, 0) == -1)
    {
        if (errno == EINTR)
        {
            kill(pid, SIGINT);
            printf("TIMEOUT\n");
            return (0);
        }
        return (-1);
    }
    if (WIFEXITED(stat))
    {
        if (WEXITSTATUS(stat) == 0)
        {
            if(verbose)
                printf("Good Fonction\n");
            return (1);
        }
        else
        {
            if (verbose)
                printf("Bad Function : code error %d\n",WEXITSTATUS(stat));
            return (0);
        }
    }
    if (WIFSIGNALED(stat))
    {
        if (verbose)
            printf("Bad function :%s\n", strsignal(WTERMSIG(stat))); // LA FAUT RAJOUTER WTERMSIG SINON CA AFFICHE UNKNOWN SIGNAL
        return (0);
    }
    return (-1);
}

void prout(void)
{
    // printf("prout\n");
    exit(0);
}

void proutok(void)
{
    // printf("proutOK\n");
    exit(0);
}

void proutnok(void)
{
    // printf("badprout\n");
    exit(1);
}

void chiasse(void)
{
    int *ptr = NULL;
    *ptr = 42;
    exit (0);
}

void dodo(void)
{
    // printf("bonne nuit\n");
    sleep(20);
    exit(0);
}

int main(void)
{
    sandbox(prout,1,1);
    sandbox(proutok,1,1);
    sandbox(proutnok,1,1);
    sandbox(chiasse,1,1);
    sandbox(dodo,1,1);
    return (0);
}