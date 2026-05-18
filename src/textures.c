/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iulian <iulian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:42:15 by iulian            #+#    #+#             */
/*   Updated: 2026/03/19 18:40:19 by iulian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	load_texture(t_game *game, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path,
			&img->width, &img->height);
	if (!img->img)
	{
		printf("Error\nFailed to load texture: %s\n", path);
		free_game(game);
		exit(1);
	}
	img->addr = mlx_get_data_addr(img->img,
			&img->bpp, &img->size_line, &img->endian);
}

void	load_textures(t_game *game)
{
	load_texture(game, &game->no_img, game->no_path);
	load_texture(game, &game->so_img, game->so_path);
	load_texture(game, &game->we_img, game->we_path);
	load_texture(game, &game->ea_img, game->ea_path);
}
