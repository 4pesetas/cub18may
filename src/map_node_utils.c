/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_node_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iulian <iulian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:30:00 by iumorave          #+#    #+#             */
/*   Updated: 2026/05/15 21:32:11 by iulian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

t_map_node	*create_node(char *str)
{
	t_map_node	*node;

	node = malloc(sizeof(t_map_node));
	if (!node)
		exit(1);
	node->line = ft_strdup(str);
	if (!node->line)
	{
		free(node);
		exit(1);
	}
	node->next = NULL;
	return (node);
}

t_map_node	*append_map_line(t_game *game, t_map_node *tail, char *line)
{
	t_map_node	*node;
	int			len;

	node = create_node(line);
	tail->next = node;
	len = ft_strlen(node->line);
	if (len > game->map_width)
		game->map_width = len;
	game->map_height++;
	return (node);
}
