/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pixel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iulian <iulian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 11:41:27 by iumorave          #+#    #+#             */
/*   Updated: 2026/05/16 23:55:00 by iulian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = game->data + (y * game->size_line + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

int	expose_hook(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

unsigned int	get_pixel_color(t_img *img, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	dst = img->addr + (y * img->size_line + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

void	clear_image(t_game *game)
{
	ft_bzero(game->data, WIDTH * HEIGHT * (game->bpp / 8));
}
