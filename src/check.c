/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:02:49 by lcollado          #+#    #+#             */
/*   Updated: 2024/01/09 16:49:51 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	valid_file(int argc, char *file, char *end)
{
	int	len;
	int	end_len;

	if (argc == 1)
		return (error("there are no args"));
	len = ft_strlen(file) - 1;
	end_len = ft_strlen(end) - 1;
	while(end_len >= 0)
	{
		if (file[len] != end[end_len])
			return (error("file extension should be .ber"));
		len--;
		end_len--;
	}
	return (1);
}

int	check_rectangular(t_map *map)
{
	int	initial_len;
	int	i;
	int	actual_len;

	initial_len = ft_strlen_nonl(map->coords[0]);
	i = 1;
	while (i < map->size.y)
	{
		actual_len = ft_strlen_nonl(map->coords[i]);
		if (actual_len != initial_len)
			return (error("the map isn't rectangular"));
		i++;
	}
	return (1);
}

int	valid_border(int x, int y, t_map *map)
{
	if ((y == 0 || x == 0 || y == map->size.y - 1 || x == map->size.x - 1)
		&& map->coords[y][x] != '1')
		return (0);
	return (1);
}

int	check_chars(t_map *map)
{
	int	i;
	int	j;
	int	p;
	int	e;

	i = -1;
	p = 0;
	e = 0;
	while (++i < map->size.y)
	{
		j = -1;
		while (++j < map->size.x)
		{
			if (map->coords[i][j] == 'P')
				p++;
			if (map->coords[i][j] == 'E')
				e++;
			if (map->coords[i][j] == 'C')
				map->total_collec++;
		}
	}
	if (p != 1 || e != 1 || map->total_collec == 0)
		return (0);
	return (1);
}

int	valid_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	if (!check_rectangular(&game->map))
		return (0);
	while (y < game->map.size.y)
	{
		x = 0;
		while (x < game->map.size.x)
		{
			if (!valid_border(x, y, &game->map))
				return (error("the border map isn't closed"));
			if (!ft_strchr("01CEP", game->map.coords[y][x]))
				return (error("there are wrong characters"));
			x++;
		}
		y++;
	}
	if (!check_chars(&game->map))
		return (error("map has to have 1 P, 1 E and at least 1 C"));
	if (!valid_path(game))
		return (error("the map doesn't have a valid path"));
	return (1);
}
