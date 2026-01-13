/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelucian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:03:51 by jelucian          #+#    #+#             */
/*   Updated: 2024/11/27 17:03:53 by jelucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *join_and_free(char *buffer, char *temp)
{
	char	*new_temp;

	new_temp = ft_strjoin(buffer, temp);
	free(buffer);
	return (new_temp);
}

char	*read_file(char *buffer, int fd)
{
	char	*temp;
	int		size_line; 

	temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));	
	size_line = 1;
	while (size_line > 0)
	{
		size_line = read(fd, temp, BUFFER_SIZE);
		if (size_line < 0)
		{
			free(buffer);
			free(temp);
			return (NULL);
		}
		temp[size_line] = '\0';
		buffer = join_and_free(buffer, temp);
		if (ft_strchr(buffer, '\n'))
			break;
	}
	free(temp);
	return (buffer);
}

char	*get_rest(char *buffer)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	rest = ft_calloc((ft_strlen(buffer) - i) + 1, sizeof(char));
	while (buffer[i])
	{
		rest[j] = buffer[i];
		j++;
		i++;
	}
	rest[j] = '\0';
	free(buffer);
	return (rest);
}

char	*get_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc((i + 2), sizeof(char));
	i = 0;	
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}


char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	buffer = read_file(buffer, fd);
	if (!buffer)
		return (NULL);
	line = get_line(buffer);
	buffer = get_rest(buffer);
	return (line);
}
/*
int	main(int argc, char **argv)
{
	int fd;

	fd = open(argv[1], 0);
	printf("%s", get_next_line(fd));
	return(0);
}*/