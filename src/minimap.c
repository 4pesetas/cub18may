/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iulian <iulian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 13:13:05 by iumorave          #+#    #+#             */
/*   Updated: 2026/05/11 19:01:42 by iulian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	fill_cell(t_rect rect, int color, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < rect.h)
	{
		j = 0;
		while (j < rect.w)
		{
			put_pixel(rect.x + j, rect.y + i, color, game);
			j++;
		}
		i++;
	}
}

static void	draw_cell(t_game *game, t_rect rect, int x, int y)
{
	rect.x = rect.offset_x + x * (BLOCK_SIZE * rect.scale);
	rect.y = rect.offset_y + y * (BLOCK_SIZE * rect.scale);
	rect.w = (BLOCK_SIZE * rect.scale) - 1;
	rect.h = (BLOCK_SIZE * rect.scale) - 1;
	if (game->map[y][x] == '1')
		fill_cell(rect, 0x994C00, game);
	else if (game->map[y][x] == '0')
		fill_cell(rect, 0x003366, game);
}

void	draw_map(t_game *game, t_rect rect)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			draw_cell(game, rect, x, y);
			x++;
		}
		y++;
	}
}
