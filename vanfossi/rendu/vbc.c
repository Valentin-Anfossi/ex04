/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:15:09 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/20 12:00:55 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int sum(char **s);
int product(char **s);
int value(char **s);

void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of input\n");
}

int check_string(char *str)
{
    int i = 0;
    int par = 0;
    char c;

    while(str[i])
    {
        c = str[i];
        if(!isdigit(c) && c != '(' && c != ')' && c!='*' && c !='+')
        {
            unexpected(c);
            return(1);
        }
        if(c == '(')
            par++;
        if(c == ')')
            par--;
        if(isdigit(c) && isdigit(str[i + 1]))
        {
            unexpected(str[i+1]);
            return (1);
        }
        i ++;
    }
    if(par > 0)
    {
        unexpected('(');
        return (1);
    }
    else if(par < 0)
    {
        unexpected(')');
        return (1);
    }
    c = str[strlen(str)-1];
    if(!isdigit(c) && (c != '(' && c != ')'))
    {
        unexpected(0);
        return (1);
    }
    return (0);
}

int value(char **s)
{
    int a;

    if(isdigit(**s))
    {
        a = **s - '0';
        (*s)++;
        return (a);
    }
    while(**s == '(')
    {
        (*s)++;
        a = sum(s);
        (*s)++;
    }
    return (a);
}

int product(char **s)
{
    int a = value(s);
    int b;
    while(**s == '*')
    {
        (*s)++;
        b = sum(s);
        a = a * b;
    }
    return (a);
}

int sum(char **s)
{
    int a = product(s);
    int b = 0;
    
    while(**s == '+')
    {
        (*s)++;
        b = product(s);
        a = a + b;  
    }
    return (a);
}

int main(int argc, char **argv)
{
    char **s;
    if(argc != 2 || !argv || !argv[1])
        return (1);
    if(check_string(argv[1]))
        return(1);
    s = &argv[1];
    printf("%d\n",sum(s));
}