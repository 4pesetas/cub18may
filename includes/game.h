/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iulian <iulian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 11:44:29 by iumorave          #+#    #+#             */
/*   Updated: 2026/05/17 12:37:35 by iulian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "mlx/mlx.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>

# define WIDTH 1280
# define HEIGHT 992
# define BLOCK_SIZE 64
# define PLAYER_HEIGHT 32.0f
# define EPSILON 0.0001
# define TOPVIEW 0
# define PI 3.14159265359

# define LEFT 65361
# define RIGHT 65363
# define UP 65362
# define DOWN 65364
# define W 119
# define A 97
# define S 115
# define D 100
# define Q 113
# define E 101
# define ESC 65307

typedef int	(*t_mlx_hook)();

typedef struct s_rect
{
	int		x;
	int		y;
	int		w;
	int		h;
	int		offset_x;
	int		offset_y;
	float	scale;
}	t_rect;

typedef struct s_map_node
{
	char				*line;
	struct s_map_node	*next;
}	t_map_node;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	t_player	player;
	int			map_width;
	int			map_height;
	char		**map;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	t_img		no_img;
	t_img		so_img;
	t_img		we_img;
	t_img		ea_img;
	int			floor_color;
	int			ceiling_color;
}	t_game;

typedef struct s_ray
{
	float	cos_a;
	float	sin_a;
	float	rx;
	float	ry;
	int		gridcell_x;
	int		gridcell_y;
	float	delta_x;
	float	delta_y;
	float	traveled_dist_x;
	float	traveled_dist_y;
	int		step_x;
	int		step_y;
	int		wall_side;
	float	dist;
	float	fix_dist;
	float	wall_height;
	int		top_wall_start;
	int		bottom_wall_end;
	float	horz_w_cord;
	t_img	*tex;
	int		tex_x_col;
	int		tex_y_row;
}	t_ray;

bool			touch(float pixelx, float pixely, t_game *game);
void			init_player(t_player *player);
void			move_player(t_game *game);
void			rotate_player(t_game *game);
void			collision(t_game *game, float new_x, float new_y);
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
int				exit_game(t_game *game);
void			free_game(t_game *game);
void			put_pixel(int x, int y, int color, t_game *game);
int				expose_hook(t_game *game);
unsigned int	get_pixel_color(t_img *img, int x, int y);
void			fill_cell(t_rect rect, int color, t_game *game);
void			draw_map(t_game *game, t_rect rect);
void			clear_image(t_game *game);
int				parse_color(char *str);
char			*check_path(char *str, char *id);
void			read_map_config(int fd, t_game *game);

bool			is_map_line(char *line);
int				no_texture(t_game *game, char *trimmed, char *line);
int				so_texture(t_game *game, char *trimmed, char *line);
int				ea_texture(t_game *game, char *trimmed, char *line);
int				we_texture(t_game *game, char *trimmed, char *line);
void			parse_map_grid(int fd, char *first_line, t_game *game);
t_map_node		*create_node(char *str);
t_map_node		*append_map_line(t_game *game, t_map_node *tail, char *line);
void			check_map_elements(t_game *game);
void			set_player_spawn(t_game *game);
void			init_game(t_game *game, char *filename);
void			load_textures(t_game *game);

int				draw_loop(t_game *game);
void			draw_background(t_game *game);
void			draw_vertical_strip(t_game *game, float ray_angle, int i);
void			init_ray(t_game *game, t_ray *ray, float ray_angle);
void			perform_dda(t_game *game, t_ray *ray);
void			calculate_wall_dims(t_game *game, t_ray *ray, float ray_angle);
void			render_wall(t_game *game, t_ray *ray, int i);
void			draw_2d_view(t_game *game, t_rect rect);
void			draw_rays(t_game *game, t_rect rect);
#endif
