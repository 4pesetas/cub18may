/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iulian <iulian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 10:19:24 by iumorave          #+#    #+#             */
/*   Updated: 2026/05/17 01:34:55 by iulian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	init_player(t_player *player)
{
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

int	key_release(int keycode, t_game *game)
{
	t_player	*player;

	player = &game->player;
	if (keycode == W || keycode == UP)
		player->key_up = false;
	if (keycode == S || keycode == DOWN)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == Q || keycode == LEFT)
		player->left_rotate = false;
	if (keycode == E || keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	t_player	*player;

	player = &game->player;
	if (keycode == ESC)
		exit_game(game);
	if (keycode == W || keycode == UP)
		player->key_up = true;
	if (keycode == S || keycode == DOWN)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == Q || keycode == LEFT)
		player->left_rotate = true;
	if (keycode == E || keycode == RIGHT)
		player->right_rotate = true;
	return (0);
}
