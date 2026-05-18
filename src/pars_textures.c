/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iulian <iulian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:30:00 by iumorave          #+#    #+#             */
/*   Updated: 2026/05/15 21:44:18 by iulian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

int	no_texture(t_game *game, char *trimmed_line, char *line)
{
	char	*path;

	path = check_path(trimmed_line, "NO");
	if (path)
	{
		if (game->no_path)
		{
			printf("Error\nDuplicate NO texture\n");
			free(line);
			free(trimmed_line);
			free_game(game);
			exit(1);
		}
		game->no_path = ft_strdup(path);
		return (1);
	}
	return (0);
}

int	so_texture(t_game *game, char *trimmed_line, char *line)
{
	char	*path;

	path = check_path(trimmed_line, "SO");
	if (path)
	{
		if (game->so_path)
		{
			printf("Error\nDuplicate SO texture\n");
			free(line);
			free(trimmed_line);
			free_game(game);
			exit(1);
		}
		game->so_path = ft_strdup(path);
		return (1);
	}
	return (0);
}

int	ea_texture(t_game *game, char *trimmed_line, char *line)
{
	char	*path;

	path = check_path(trimmed_line, "EA");
	if (path)
	{
		if (game->ea_path)
		{
			printf("Error\nDuplicate EA texture\n");
			free(line);
			free(trimmed_line);
			free_game(game);
			exit(1);
		}
		game->ea_path = ft_strdup(path);
		return (1);
	}
	return (0);
}

int	we_texture(t_game *game, char *trimmed_line, char *line)
{
	char	*path;

	path = check_path(trimmed_line, "WE");
	if (path)
	{
		if (game->we_path)
		{
			printf("Error\nDuplicate WE texture\n");
			free(line);
			free(trimmed_line);
			free_game(game);
			exit(1);
		}
		game->we_path = ft_strdup(path);
		return (1);
	}
	return (0);
}
