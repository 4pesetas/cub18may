/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iumorave <iumorave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:24:52 by iumorave          #+#    #+#             */
/*   Updated: 2024/12/09 10:20:08 by iumorave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	free_stuff(char *buffer, char *stash)
{
	free(buffer);
	free(stash);
}

char	*fill_stash(int fd, char *stash, char *buffer, ssize_t read_bytes)
{
	char	*temp;

	if (!stash)
		stash = ft_strdup("");
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free_stuff(buffer, stash);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		temp = ft_strjoin(stash, buffer);
		if (!temp)
		{
			free_stuff(buffer, stash);
			return (NULL);
		}
		free(stash);
		stash = temp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (free(buffer), stash);
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
	static char	*stash;
	char		*buffer;
	char		*line;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free_stuff(buffer, stash);
		stash = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (buffer == NULL)
		return (NULL);
	stash = fill_stash(fd, stash, buffer, 1);
	if (stash == NULL)
		return (NULL);
	if (*stash == '\0')
	{
		free(stash);
		return (stash = NULL);
	}
	line = take_line(stash);
	stash = take_rest(stash);
	return (line);
}

/*int	main(int ac, char **av)
{
	int	fd;
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
	if (fd == -1)
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
	return 0;
}*/
