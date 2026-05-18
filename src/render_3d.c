/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iulian <iulian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 21:28:30 by iulian            #+#    #+#             */
/*   Updated: 2026/05/17 01:15:15 by iulian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

static void	set_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->wall_side == 0 && ray->step_x > 0)
		ray->tex = &game->we_img;
	else if (ray->wall_side == 0)
		ray->tex = &game->ea_img;
	else if (ray->step_y > 0)
		ray->tex = &game->no_img;
	else
		ray->tex = &game->so_img;
}

void	calculate_wall_dims(t_game *game, t_ray *ray, float ray_angle)
{
	if (ray->wall_side == 0)
		ray->dist = (ray->traveled_dist_x - ray->delta_x);
	else
		ray->dist = (ray->traveled_dist_y - ray->delta_y);
	ray->fix_dist = ray->dist * cos(ray_angle - game->player.angle);
	if (ray->fix_dist < 0.1f)
		ray->fix_dist = 0.1f;
	ray->wall_height = (BLOCK_SIZE / ray->fix_dist) * (HEIGHT / 3.6f);
	ray->top_wall_start = (HEIGHT - ray->wall_height) / 2;
	ray->bottom_wall_end = ray->top_wall_start + ray->wall_height;
	if (ray->wall_side == 0)
		ray->horz_w_cord = (game->player.y + ray->dist * ray->sin_a);
	else
		ray->horz_w_cord = (game->player.x + ray->dist * ray->cos_a);
	ray->horz_w_cord -= floor(ray->horz_w_cord / BLOCK_SIZE) * BLOCK_SIZE;
	set_wall_texture(game, ray);
}

static void	get_tex_coords(t_ray *ray, int wall_y)
{
	ray->tex_x_col = (int)(ray->horz_w_cord / BLOCK_SIZE * ray->tex->width);
	ray->tex_y_row = (int)((float)(wall_y - ray->top_wall_start)
			/ ray->wall_height * ray->tex->height);
	if (ray->tex_x_col < 0)
		ray->tex_x_col = 0;
	if (ray->tex_x_col >= ray->tex->width)
		ray->tex_x_col = ray->tex->width - 1;
	if (ray->tex_y_row < 0)
		ray->tex_y_row = 0;
	if (ray->tex_y_row >= ray->tex->height)
		ray->tex_y_row = ray->tex->height - 1;
}

void	render_wall(t_game *game, t_ray *ray, int i)
{
	int				wall_y;
	int				draw_end;
	unsigned int	color;

	wall_y = ray->top_wall_start;
	if (wall_y < 0)
		wall_y = 0;
	draw_end = ray->bottom_wall_end;
	if (draw_end > HEIGHT)
		draw_end = HEIGHT;
	while (wall_y < draw_end)
	{
		get_tex_coords(ray, wall_y);
		color = get_pixel_color(ray->tex, ray->tex_x_col, ray->tex_y_row);
		if (ray->wall_side == 1)
			color = (color >> 1) & 0x7F7F7F;
		put_pixel(i, wall_y, color, game);
		wall_y++;
	}
}
