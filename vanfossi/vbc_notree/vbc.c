/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 00:18:42 by vanfossi          #+#    #+#             */
/*   Updated: 2026/01/18 12:18:48 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"

//ALL TESTS OK!!

void unexpected(char c)
{
    if(c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of file\n");
}

int check_string(char *s)
{
    int i = 0;
    int par = 0;

    while(s[i]) //Si pas un char valide ou si nombre a 2 chiffres
    {
        if(s[i] == '(')
            par ++;
        else if(s[i] == ')')
            par --;
        else if(!isdigit(s[i]) && s[i] != '+' && s[i] != '*' && s[i] != '(' && s[i] != ')')
            return (unexpected(s[i]),1);
        if(isdigit(s[i]) && isdigit(s[i+1]))
            return (unexpected(s[i+1]),1);
        i ++;
    }
    if(par > 0) //Si parentheses non fermes
        return (unexpected('('),1);
    else if(par < 0) //Si parentheses non ouvertes
        return (unexpected(')'),1);
    if(s[strlen(s)-1] == '+' || s[strlen(s)-1] == '*') //Si le dernier char est un +/*
        return (unexpected(0),1);
    return (0);
}

int factor(char **s)
{
    int n = 0;
    if(isdigit(**s))
    {
        n = **s - '0';
        (*s)++;
        return(n);
    }
    while(**s == '(') //On croise une parenthese ouvrante donc on retourne dans sum pour recommencer
    {
        (*s)++;
        n = sum(s);
        (*s)++;
    }
    return (n);
}

int product(char **s) 
{
    int prod1 = factor(s);
    int prod2;
    while(**s == '*')
    {
        (*s)++;
        prod2 = factor(s);
        prod1 = prod1 * prod2;
    }
    return (prod1);
}

int sum(char **s) 
{
    int sum1 = product(s);
    int sum2;

    while(**s == '+')
    {
        (*s)++;
        sum2 = product(s);
        sum1 = sum1 + sum2;
    }
    return (sum1);
}

int main(int argc, char **argv) 
{
    char **s;
    if (argc != 2)
        return (1);
    if (check_string(argv[1])) // au lieu de faire un binary tree, on check la string 
        return (1);
    s = &argv[1]; //on passe l'adresse de la string pour avoir un double pointeur
    // ca permet de l'incrementer dans les fonctions recursives
    int r = sum(s);
    printf("%d\n", r);
    return (0);
}
