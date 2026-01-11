/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 11:16:28 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/10 11:26:19 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int picoshell(char **cmds[]);

int main(void)
{
    char *echo_cmd[] = {"echo","prout",0};
    char *ls_cmd[]   = {"ls","-l",0};

    char **cmds[] = {
        echo_cmd,
        ls_cmd
    };
    picoshell(cmds);
}