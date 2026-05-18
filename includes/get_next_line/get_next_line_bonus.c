/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iulian <iulian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:24:52 by iumorave          #+#    #+#             */
/*   Updated: 2026/05/18 14:14:59 by iulian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*fill_stash(int fd, char *stash, char *buffer)
{
	ssize_t	read_bytes;

	read_bytes = 1;
	if (!stash)
		stash = ft_strdup("");
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (stash);
}

char	*take_line(char *stash)
{
	int		i;
	int		len;
	char	*line;

	i = 0;
	len = 0;
	if (stash == NULL)
		return (NULL);
	while (stash[len] != '\n' && stash[len])
		len++;
	if (stash[len] == '\n')
		len++;
	line = ft_calloc(sizeof(char), len + 1);
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*take_rest(char *stash)
{
	int		i;
	int		len;
	char	*rest;

	i = 0;
	len = 0;
	if (stash == NULL)
		return (NULL);
	while (stash[len] != '\n' && stash[len])
		len++;
	if (stash[len] == '\n')
		len++;
	rest = ft_calloc(sizeof(char), ft_strlen(stash) - len + 1);
	if (!rest)
		return (NULL);
	while (stash[len + i])
	{
		rest[i] = stash[len + i];
		i++;
	}
	free(stash);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*buffer;
	char		*line;

	if (fd < 0 || fd >= MAX_FD)
		return (NULL);
	line = NULL;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash[fd]);
		free(buffer);
		stash[fd] = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (buffer == NULL)
		return (NULL);
	stash[fd] = fill_stash(fd, stash[fd], buffer);
	if (!stash[fd] || *stash[fd] == '\0')
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	line = take_line(stash[fd]);
	stash[fd] = take_rest(stash[fd]);
	return (line);
}

/*int	main(int ac, char **av)
{
	int		fd;
	int		fd2;
	char	*line;

	if (ac < 2)
	{
		printf("arg needed: a.out fichier.txt or '0'");
		return 0;
	}
	if (av[1][0] == '0')
		fd = 0;
	else
		fd = open(av[1], O_RDONLY);
		fd2 = open(av[1], av[2], O_RDONLY);
	if (fd == -1 || fd2 == -1)
	{
		printf("Read error");
		return 1;
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		printf(">> %s", line);
		free(line);
		getchar();
	}
	close(fd);
	close(fd2);
	return 0;
}*/