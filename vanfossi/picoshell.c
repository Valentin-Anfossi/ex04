/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 11:15:35 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/11 13:08:30 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int picoshell(char **cmds[])
{
    int i = 0; 
    int pid;
    int pi[2];
    int previous_fd = -1;


    while(cmds[i])
    {
        if(cmds[i+1])
        {
            if(pipe(pi) == -1)
                return (1);
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
            if(i == 0)
            {
                close(pi[1]);
                dup2(STDOUT_FILENO,pi[0]);
            }
            execvp(cmds[i][0],cmds[i]);
            exit (0);
        }
        i ++;

        
    }

    while(wait(0) > 0)
        ;
    printf("done\n");
    exit(0);
}