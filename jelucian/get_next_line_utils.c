/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelucian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:04:05 by jelucian          #+#    #+#             */
/*   Updated: 2024/11/27 17:04:06 by jelucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len1;
	int		len2;
	int		j;
	int		i;
	char	*str;

	j = 0;
	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc(len1 + len2 + 1);
	if (!str)
		return (NULL);
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	while (j < len2)
	{
		str[len1 + j] = s2[j];
		j++;
	}
	str[len1 + len2] = '\0';
	return (str);
}

void	*ft_calloc(size_t nbelem, size_t size)
{
	void	*tab0;
	size_t	i;

	i = 0;
	if (nbelem != 0 && (INT_MAX / nbelem) < size)
		return (NULL);
	tab0 = malloc(nbelem * size);
	if (!tab0)
		return (tab0);
	while (i < size)
	{
		*(unsigned char *)(tab0 + i) = '\0';
		i++;
	}
	return (tab0);
}  
/*
int	main()
{
	int fd = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return (0);
}*/
