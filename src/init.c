/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iulian <iulian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:43:24 by iulian            #+#    #+#             */
/*   Updated: 2026/05/17 12:37:35 by iulian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

static void	init_error(t_game *game, char *msg)
{
	printf("%s\n", msg);
	free_game(game);
	exit(1);
}

void	init_game_struct(t_game *game)
{
	game->floor_color = -1;
	game->ceiling_color = -1;
	game->no_path = NULL;
	game->so_path = NULL;
	game->we_path = NULL;
	game->ea_path = NULL;
	game->no_img.img = NULL;
	game->so_img.img = NULL;
	game->we_img.img = NULL;
	game->ea_img.img = NULL;
	game->map = NULL;
	game->img = NULL;
	game->win = NULL;
	game->mlx = NULL;
	init_player(&game->player);
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		init_error(game, "MLX init failed");
	load_textures(game);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "game");
	if (!game->win)
		init_error(game, "Window creation failed");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		init_error(game, "Image creation failed");
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	init_game(t_game *game, char *filename)
{
	int	fd;

	init_game_struct(game);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCould not open file %s\n", filename);
		exit(1);
	}
	read_map_config(fd, game);
	close(fd);
	check_map_elements(game);
	set_player_spawn(game);
	init_mlx(game);
}
