/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 11:16:28 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/12 15:08:45 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int picoshell(char **cmds[]);

int main(void)
{
    char *echo_cmd[] = {"ls","-l", NULL};
    char *ls_cmd[]   = {"cat","-e",NULL};
    char *error_cmd[] = {"cat", "-e",NULL};

    char **cmds[] = {
        echo_cmd,
        ls_cmd,
        error_cmd,
        NULL
    };
    picoshell(cmds);
}