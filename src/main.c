/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iulian <iulian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 12:15:24 by iumorave          #+#    #+#             */
/*   Updated: 2026/05/16 23:55:53 by iulian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

bool	touch(float pixelx, float pixely, t_game *game)
{
	int	x;
	int	y;

	if (pixelx < 0 || pixely < 0)
		return (true);
	x = (int)(pixelx / BLOCK_SIZE);
	y = (int)(pixely / BLOCK_SIZE);
	if (x >= game->map_width || y >= game->map_height)
		return (true);
	return (game->map[y][x] == '1' || game->map[y][x] == ' ');
}

static void	check_args(int argc, char **argv)
{
	char	*ext;

	if (argc != 2)
	{
		printf("Error\nUsage: ./game <map.cub>\n");
		exit(1);
	}
	ext = ft_strrchr(argv[1], '.');
	if (!ext || ft_strncmp(ext, ".cub", 5) != 0)
	{
		printf("Error\nFile must be .cub\n");
		exit(1);
	}
}

static void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, (t_mlx_hook)key_press, game);
	mlx_hook(game->win, 3, 1L << 1, (t_mlx_hook)key_release, game);
	mlx_hook(game->win, 17, 0, (t_mlx_hook)exit_game, game);
	mlx_expose_hook(game->win, (t_mlx_hook)expose_hook, game);
	mlx_loop_hook(game->mlx, (t_mlx_hook)draw_loop, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game	game;

	check_args(argc, argv);
	init_game(&game, argv[1]);
	setup_hooks(&game);
	return (0);
}
