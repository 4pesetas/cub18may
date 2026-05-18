/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_config_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iulian <iulian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 17:55:32 by iulian            #+#    #+#             */
/*   Updated: 2026/05/17 12:34:57 by iulian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

static int	get_rgb_digits(char **str, bool last)
{
	int	val;

	while (**str == ' ' || **str == '\t')
		(*str)++;
	if (!ft_isdigit(**str))
		return (-1);
	val = ft_atoi(*str);
	while (**str && ft_isdigit(**str))
		(*str)++;
	while (**str == ' ' || **str == '\t')
		(*str)++;
	if (!last)
	{
		if (**str != ',')
			return (-1);
		(*str)++;
	}
	if (val < 0 || val > 255)
		return (-1);
	return (val);
}

int	parse_color(char *str)
{
	int	r;
	int	g;
	int	b;

	r = get_rgb_digits(&str, false);
	g = get_rgb_digits(&str, false);
	b = get_rgb_digits(&str, true);
	if (r == -1 || g == -1 || b == -1)
		return (-1);
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str != '\0')
		return (-1);
	return (r << 16 | g << 8 | b);
}

char	*check_path(char *str, char *id)
{
	int	len;

	len = ft_strlen(id);
	if (ft_strncmp(str, id, len) == 0 && (str[len] == ' ' || str[len] == '\t'))
	{
		str += len;
		while (*str == ' ' || *str == '\t')
			str++;
		return (str);
	}
	return (NULL);
}

bool	is_map_line(char *line)
{
	int		i;
	bool	valid_char;

	valid_char = false;
	if (!line || line[0] == '\0' || line[0] == '\n')
		return (false);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0'
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W')
			return (false);
		if (line[i] != ' ')
			valid_char = true;
		i++;
	}
	return (valid_char);
}
