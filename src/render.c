/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iulian <iulian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:44:32 by iulian            #+#    #+#             */
/*   Updated: 2026/05/16 20:04:01 by iulian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	draw_background(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				put_pixel(x, y, game->ceiling_color, game);
			else
				put_pixel(x, y, game->floor_color, game);
			x++;
		}
		y++;
	}
}

void	draw_vertical_strip(t_game *game, float ray_angle, int i)
{
	t_ray	ray;

	init_ray(game, &ray, ray_angle);
	perform_dda(game, &ray);
	calculate_wall_dims(game, &ray, ray_angle);
	render_wall(game, &ray, i);
}

static void	render_minimap_overlay(t_game *game)
{
	float	scale;
	t_rect	rect;

	scale = 0.25f;
	rect.scale = scale;
	rect.offset_x = WIDTH - (game->map_width * BLOCK_SIZE * scale) - 20;
	rect.offset_y = 20;
	draw_2d_view(game, rect);
}

static void	render_3d_view(t_game *game)
{
	float	fov;
	float	start_angle;
	float	angle_step;
	int		i;

	draw_background(game);
	fov = PI / 3;
	start_angle = game->player.angle - fov / 2.0f;
	angle_step = fov / WIDTH;
	i = 0;
	while (i < WIDTH)
	{
		draw_vertical_strip(game, start_angle + (i * angle_step), i);
		i++;
	}
	if (!TOPVIEW)
		render_minimap_overlay(game);
}

int	draw_loop(t_game *game)
{
	float	scale;
	t_rect	rect;

	move_player(game);
	clear_image(game);
	if (TOPVIEW)
	{
		scale = (float)WIDTH / (float)(game->map_width * BLOCK_SIZE);
		if ((float)HEIGHT / (float)(game->map_height * BLOCK_SIZE) < scale)
			scale = (float)HEIGHT / (float)(game->map_height * BLOCK_SIZE);
		if (scale > 1.0f)
			scale = 1.0f;
		rect.scale = scale;
		rect.offset_x = (WIDTH - (game->map_width * BLOCK_SIZE * scale)) / 2;
		rect.offset_y = 0;
		draw_2d_view(game, rect);
	}
	else
		render_3d_view(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
