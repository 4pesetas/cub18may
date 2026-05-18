/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_spawn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iulian <iulian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:25:20 by iulian            #+#    #+#             */
/*   Updated: 2026/03/19 21:41:55 by iulian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

static void	set_player_angle(t_player *player, char c)
{
	if (c == 'N')
		player->angle = 3 * PI / 2.0f;
	else if (c == 'S')
		player->angle = PI / 2.0f;
	else if (c == 'E')
		player->angle = 0.0f;
	else if (c == 'W')
		player->angle = PI;
}

static void	init_spawn(t_game *game, int y, int x, bool *found)
{
	if (*found)
	{
		printf("Error\nMultiple player positions\n");
		free_game(game);
		exit(1);
	}
	game->player.x = x * BLOCK_SIZE + (BLOCK_SIZE / 2.0f);
	game->player.y = y * BLOCK_SIZE + (BLOCK_SIZE / 2.0f);
	set_player_angle(&game->player, game->map[y][x]);
	game->map[y][x] = '0';
	*found = true;
}

void	set_player_spawn(t_game *game)
{
	int		y;
	int		x;
	bool	found;

	found = false;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (ft_strchr("NSEW", game->map[y][x]))
				init_spawn(game, y, x, &found);
			x++;
		}
		y++;
	}
	if (!found)
	{
		printf("Error\nNo player spawn found in map\n");
		free_game(game);
		exit(1);
	}
}
