/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 03:22:34 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/20 03:28:43 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    int pid = 0;
    for(int i = 0; i < 10; i ++)
    {
        pid = fork();
        if(pid == 0)
        {
            sleep(2);
            exit(i%2);
        }
    }
    int stat;
    while(wait(&stat) > -1)
    {
        printf("%d %d \n",stat,WEXITSTATUS(stat));
    }
    exit(0);
}