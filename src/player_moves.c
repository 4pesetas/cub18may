/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iulian <iulian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 18:52:44 by iumorave          #+#    #+#             */
/*   Updated: 2026/05/17 16:18:23 by iulian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

static void	move_forw_back(t_player *player, float *dx, float *dy)
{
	float	cos_a;
	float	sin_a;

	cos_a = cos(player->angle);
	sin_a = sin(player->angle);
	if (player->key_up)
	{
		*dx += cos_a;
		*dy += sin_a;
	}
	if (player->key_down)
	{
		*dx -= cos_a;
		*dy -= sin_a;
	}
}

static void	move_left_right(t_player *player, float *dx, float *dy)
{
	float	cos_a;
	float	sin_a;

	cos_a = cos(player->angle);
	sin_a = sin(player->angle);
	if (player->key_left)
	{
		*dx += sin_a;
		*dy -= cos_a;
	}
	if (player->key_right)
	{
		*dx -= sin_a;
		*dy += cos_a;
	}
}

void	move_player(t_game *game)
{
	float		dx;
	float		dy;
	float		movement_length;

	dx = 0;
	dy = 0;
	move_forw_back(&game->player, &dx, &dy);
	move_left_right(&game->player, &dx, &dy);
	movement_length = sqrt(dx * dx + dy * dy);
	if (movement_length > EPSILON)
	{
		dx = (dx / movement_length) * 2.0f;
		dy = (dy / movement_length) * 2.0f;
	}
	rotate_player(game);
	collision(game, game->player.x + dx, game->player.y + dy);
}

void	collision(t_game *game, float new_x, float new_y)
{
	t_player	*player;

	player = &game->player;
	if (!touch(new_x, player->y, game))
		player->x = new_x;
	if (!touch(player->x, new_y, game))
		player->y = new_y;
}

void	rotate_player(t_game *game)
{
	t_player	*player;
	float		angle_step;

	angle_step = 0.03f;
	player = &game->player;
	if (player->left_rotate)
		player->angle -= angle_step;
	if (player->right_rotate)
		player->angle += angle_step;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	else if (player->angle < 0)
		player->angle += 2 * PI;
}
