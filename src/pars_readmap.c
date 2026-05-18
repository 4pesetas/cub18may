/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_readmap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iulian <iulian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 16:46:32 by iumorave          #+#    #+#             */
/*   Updated: 2026/05/17 13:11:51 by iulian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

static void	exit_and_free(char *msg, char *id, char *line, t_game *game)
{
	printf("Error\n%s %s\n", msg, id);
	free(line);
	free_game(game);
	exit(1);
}

static int	floor_ceil_conf(t_game *game, char *trimmed, char *line, char *id)
{
	char	*color_id;
	int		rgb_string;
	int		*target;

	color_id = check_path(trimmed, id);
	if (!color_id)
		return (0);
	if (id[0] == 'F')
		target = &game->floor_color;
	else
		target = &game->ceiling_color;
	if (*target != -1)
	{
		free(trimmed);
		exit_and_free("Duplicate color identifier:", id, line, game);
	}
	rgb_string = parse_color(color_id);
	if (rgb_string == -1)
	{
		free(trimmed);
		exit_and_free("Invalid color format for:", id, line, game);
	}
	*target = rgb_string;
	return (1);
}

static int	process_config_line(t_game *game, char *trimmed, char *line, int fd)
{
	int	len;

	if (!trimmed || !*trimmed)
		return (1);
	if (no_texture(game, trimmed, line)
		|| so_texture(game, trimmed, line)
		|| ea_texture(game, trimmed, line)
		|| we_texture(game, trimmed, line)
		|| floor_ceil_conf(game, trimmed, line, "F")
		|| floor_ceil_conf(game, trimmed, line, "C"))
		return (1);
	if (is_map_line(line))
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		parse_map_grid(fd, line, game);
		return (2);
	}
	printf("Error\nInvalid line in configuration: %s\n", trimmed);
	return (-1);
}

static void	check_garbage_after_map(int fd, t_game *game)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, " \t\n");
		if (*trimmed)
		{
			printf("Error\nInvalid or empty line in map config\n");
			free(trimmed);
			free(line);
			free_game(game);
			exit(1);
		}
		free(trimmed);
		free(line);
		line = get_next_line(fd);
	}
}

void	read_map_config(int fd, t_game *game)
{
	char	*line;
	char	*trimmed;
	int		status;

	line = get_next_line(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, " \t\n");
		status = process_config_line(game, trimmed, line, fd);
		free(trimmed);
		free(line);
		if (status == 2)
		{
			check_garbage_after_map(fd, game);
			break ;
		}
		if (status == -1)
		{
			free_game(game);
			exit(1);
		}
		line = get_next_line(fd);
	}
}
