/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 11:15:35 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/12 23:44:09 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int picoshell(char **cmds[])
{
    int i = 0;
    int fd[2];
    int old_fd = -1;
    pid_t pid;
    
    while(cmds[i])
    {
        if(cmds[i+1])
        {
            if(pipe(fd) == -1)
                return (1);
        }
        
        pid = fork();
        if(pid == -1)
        {
            if(cmds[i+1])
            {
                close(fd[0]);
                close(fd[1]);
            }
            return (1);
        }
        if(pid == 0)
        {
            if(cmds[i + 1])
            {
                dup2(fd[1],STDOUT_FILENO);
                close(fd[1]);
                close(fd[0]);
            }
            if(old_fd != -1)
            {
                dup2(old_fd,STDIN_FILENO);
                close(old_fd);
            }
            execvp(cmds[i][0],cmds[i]);
            printf("bou\n");
            exit(1);
        }
        if (old_fd != -1)
            close(old_fd);
        if(cmds[i+1])
        {
            old_fd = fd[0];
            close(fd[1]);
        }
        i++;
    }
    int error = 0;
    int r_error = 0;
    while(wait(&error) > 0)
    {
        if(error != 0)
            r_error = 1;
        ;
    }
    return (r_error);
}