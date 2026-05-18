/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_rawdata_2grid.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iulian <iulian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:30:00 by iumorave          #+#    #+#             */
/*   Updated: 2026/05/15 21:31:04 by iulian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

static char	*pad_map_row(t_map_node *node, int width)
{
	int		len;
	char	*row;

	len = ft_strlen(node->line);
	row = malloc(width + 1);
	if (!row)
		exit(1);
	ft_memcpy(row, node->line, len);
	while (len < width)
	{
		row[len] = ' ';
		len++;
	}
	row[width] = '\0';
	return (row);
}

static void	fill_map_array(t_game *game, t_map_node *node)
{
	int			y;
	t_map_node	*next;

	y = 0;
	while (node)
	{
		game->map[y++] = pad_map_row(node, game->map_width);
		next = node->next;
		free(node->line);
		free(node);
		node = next;
	}
	game->map[y] = NULL;
}

static int	check_and_append_line(t_game *game, t_map_node **tail, char *line)
{
	char	*tmp;

	if (is_map_line(line))
	{
		*tail = append_map_line(game, *tail, line);
		free(line);
		return (1);
	}
	tmp = ft_strtrim(line, " \t\n");
	if (tmp && *tmp)
	{
		printf("Error\nInvalid line  %s\n", tmp);
		free(tmp);
		free(line);
		free_game(game);
		exit(1);
	}
	free(tmp);
	free(line);
	return (0);
}

static t_map_node	*read_map_lines(int fd, char *fline, t_game *game)
{
	t_map_node	*head;
	t_map_node	*tail;
	char		*line;
	int			len;

	head = create_node(fline);
	tail = head;
	game->map_width = ft_strlen(fline);
	game->map_height = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (!check_and_append_line(game, &tail, line))
			break ;
	}
	return (head);
}

void	parse_map_grid(int fd, char *first_line, t_game *game)
{
	t_map_node	*head;

	head = read_map_lines(fd, first_line, game);
	game->map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!game->map)
		exit(1);
	fill_map_array(game, head);
}
