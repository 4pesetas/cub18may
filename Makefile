NAME = cub3d

CC = gcc-14
GNL_PATH = includes/get_next_line
LIBFT_PATH = includes/libft
LIBFT_LIB = $(LIBFT_PATH)/libft.a

CFLAGS = -Wall -Wextra -Werror -I/usr/include -Imlx -Iincludes -I$(GNL_PATH) -I$(LIBFT_PATH)
SRC_DIR = src
SRC_FILES = main.c \
			player_init.c \
			player_moves.c \
			free.c \
			utils_pixel.c \
			minimap.c \
			map_config_utils.c \
			pars_readmap.c \
			pars_textures.c \
			rawdata_2grid.c \
			map_node_utils.c \
			map_valid_char.c \
			player_spawn.c \
			init.c \
			render.c \
			render_dda.c \
			render_2d.c \
			render_3d.c \
			textures.c


SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES)) \
		$(GNL_PATH)/get_next_line.c $(GNL_PATH)/get_next_line_utils.c
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

MLX_PATH = includes/mlx
MLX_LIB = includes/mlx/libmlx_Linux.a

MLX_FLAGS = $(MLX_LIB) $(LIBFT_LIB) -L/usr/lib -lXext -lX11 -lm

all: $(LIBFT_LIB) $(MLX_LIB) $(OBJ_DIR) $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_PATH)

$(MLX_LIB):
	@make -C $(MLX_PATH)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/game.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(GNL_PATH)/%.c includes/game.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
