/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iulian <iulian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 20:00:44 by iumorave          #+#    #+#             */
/*   Updated: 2026/03/19 19:50:56 by iulian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

static void	free_map(t_game *game)
{
	int	i;

	if (!game->map)
		return ;
	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	game->map = NULL;
}

static void	free_textures(t_game *game)
{
	if (game->no_img.img)
		mlx_destroy_image(game->mlx, game->no_img.img);
	if (game->so_img.img)
		mlx_destroy_image(game->mlx, game->so_img.img);
	if (game->we_img.img)
		mlx_destroy_image(game->mlx, game->we_img.img);
	if (game->ea_img.img)
		mlx_destroy_image(game->mlx, game->ea_img.img);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
}

void	free_game(t_game *game)
{
	get_next_line(-1);
	if (game->no_path)
		free(game->no_path);
	if (game->so_path)
		free(game->so_path);
	if (game->we_path)
		free(game->we_path);
	if (game->ea_path)
		free(game->ea_path);
	free_map(game);
	if (game->mlx)
	{
		free_textures(game);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

int	exit_game(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}
