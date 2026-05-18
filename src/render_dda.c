/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_dda.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iulian <iulian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 21:15:23 by iulian            #+#    #+#             */
/*   Updated: 2026/05/16 19:49:10 by iulian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

static void	init_ray_x(t_ray *ray)
{
	if (fabsf(ray->cos_a) < EPSILON)
		ray->delta_x = INFINITY;
	else
		ray->delta_x = fabsf(BLOCK_SIZE / ray->cos_a);
	if (ray->cos_a < 0)
	{
		ray->step_x = -1;
		ray->traveled_dist_x = (ray->rx - ray->gridcell_x * BLOCK_SIZE)
			*(ray->delta_x / BLOCK_SIZE);
	}
	else
	{
		ray->step_x = 1;
		ray->traveled_dist_x = ((ray->gridcell_x + 1) * BLOCK_SIZE - ray->rx)
			*(ray->delta_x / BLOCK_SIZE);
	}
}

static void	init_ray_y(t_ray *ray)
{
	if (fabsf(ray->sin_a) < EPSILON)
		ray->delta_y = INFINITY;
	else
		ray->delta_y = fabsf(BLOCK_SIZE / ray->sin_a);
	if (ray->sin_a < 0)
	{
		ray->step_y = -1;
		ray->traveled_dist_y = (ray->ry - ray->gridcell_y * BLOCK_SIZE)
			*(ray->delta_y / BLOCK_SIZE);
	}
	else
	{
		ray->step_y = 1;
		ray->traveled_dist_y = ((ray->gridcell_y + 1) * BLOCK_SIZE - ray->ry)
			*(ray->delta_y / BLOCK_SIZE);
	}
}

void	init_ray(t_game *game, t_ray *ray, float ray_angle)
{
	ray->cos_a = cos(ray_angle);
	ray->sin_a = sin(ray_angle);
	ray->rx = game->player.x;
	ray->ry = game->player.y;
	ray->gridcell_x = (int)(ray->rx / BLOCK_SIZE);
	ray->gridcell_y = (int)(ray->ry / BLOCK_SIZE);
	init_ray_x(ray);
	init_ray_y(ray);
}

void	perform_dda(t_game *game, t_ray *ray)
{
	bool	hit;

	hit = false;
	while (!hit)
	{
		if (ray->traveled_dist_x < ray->traveled_dist_y)
		{
			ray->traveled_dist_x += ray->delta_x;
			ray->gridcell_x += ray->step_x;
			ray->wall_side = 0;
		}
		else
		{
			ray->traveled_dist_y += ray->delta_y;
			ray->gridcell_y += ray->step_y;
			ray->wall_side = 1;
		}
		if (ray->gridcell_x < 0 || ray->gridcell_x >= game->map_width
			|| ray->gridcell_y < 0 || ray->gridcell_y >= game->map_height)
			break ;
		if (game->map[ray->gridcell_y][ray->gridcell_x] == '1')
			hit = true;
	}
}
