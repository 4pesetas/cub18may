/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iulian <iulian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:20:21 by iulian            #+#    #+#             */
/*   Updated: 2026/05/17 12:37:35 by iulian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

static void	error_wall(t_game *game, char c)
{
	if (c == '0')
		printf("Error\nMap is not closed by walls\n");
	else
		printf("Error\nPlayer spawn is not closed by walls\n");
	free_game(game);
	exit(1);
}

static void	error_space(t_game *game, char c)
{
	if (c == '0')
		printf("Error\nMap has a space hole or open wall\n");
	else
		printf("Error\nPlayer spawn is exposed to open space\n");
	free_game(game);
	exit(1);
}

static void	check_edge_and_space(t_game *game, int y, int x)
{
	char	c;

	c = game->map[y][x];
	if (y == 0 || y == game->map_height - 1)
		error_wall(game, c);
	if (x == 0 || x == game->map_width - 1)
		error_wall(game, c);
	if (game->map[y - 1][x] == ' ' || game->map[y + 1][x] == ' ')
		error_space(game, c);
	if (game->map[y][x - 1] == ' ' || game->map[y][x + 1] == ' ')
		error_space(game, c);
}

static void	valid_chars_enclosed(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (ft_strchr("0NSEW", game->map[y][x]))
				check_edge_and_space(game, y, x);
			x++;
		}
		y++;
	}
}

void	check_map_elements(t_game *game)
{
	if (!game->no_path || !game->so_path || !game->we_path || !game->ea_path
		|| game->floor_color == -1 || game->ceiling_color == -1 || !game->map)
	{
		printf("Error\nMissing map configuration elements.\n");
		free_game(game);
		exit(1);
	}
	valid_chars_enclosed(game);
}
