/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iulian <iulian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 21:28:15 by iulian            #+#    #+#             */
/*   Updated: 2026/05/17 16:42:33 by iulian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

static void	draw_single_ray(t_game *game, t_ray *ray, t_rect rect)
{
	int		step;
	int		pixelx;
	int		pixely;

	perform_dda(game, ray);
	if (ray->wall_side == 0)
		ray->dist = (ray->traveled_dist_x - ray->delta_x);
	else
		ray->dist = (ray->traveled_dist_y - ray->delta_y);
	step = 0;
	while (step < ray->dist * rect.scale)
	{
		pixelx = rect.offset_x + (game->player.x * rect.scale)
			+ ray->cos_a * step;
		pixely = rect.offset_y + (game->player.y * rect.scale)
			+ ray->sin_a * step;
		if (pixelx >= 0 && pixelx < WIDTH && pixely >= 0 && pixely < HEIGHT)
			put_pixel(pixelx, pixely, 0x00FF00, game);
		step++;
	}
}

void	draw_rays(t_game *game, t_rect rect)
{
	t_ray	ray;
	int		i;
	int		num_rays;
	float	fov;

	num_rays = 120;
	fov = PI / 3;
	i = 0;
	while (i < num_rays)
	{
		init_ray(game, &ray, (game->player.angle - fov / 2.0f)
			+ (((float)i / (num_rays - 1)) * fov));
		draw_single_ray(game, &ray, rect);
		i++;
	}
}

void	draw_2d_view(t_game *game, t_rect rect)
{
	int		player_size;
	int		player_dir;
	t_rect	player_rect;

	draw_map(game, rect);
	draw_rays(game, rect);
	player_size = 4;
	player_rect.x = rect.offset_x + game->player.x * rect.scale
		- (float)player_size / 2.0f;
	player_rect.y = rect.offset_y + game->player.y * rect.scale
		- (float)player_size / 2.0f;
	player_rect.w = player_size;
	player_rect.h = player_size;
	fill_cell(player_rect, 0xFF0000, game);
	player_dir = 0;
	while (player_dir < 12)
	{
		put_pixel(player_rect.x + player_size / 2.0f
			+ cos(game->player.angle) * player_dir,
			player_rect.y + player_size / 2.0f
			+ sin(game->player.angle) * player_dir,
			0xFF0000, game);
		player_dir++;
	}
}
