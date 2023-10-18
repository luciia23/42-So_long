/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:02:49 by lcollado          #+#    #+#             */
/*   Updated: 2023/10/18 13:34:43 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	valid_file(int argc, char *file)
{
	int	len;
	
	if (argc == 1)
		return (error("there are no args"));
	len = ft_strlen(file);
	if (!ft_strnstr(file, ".ber", len))
		return (error("file extension should be .ber"));
	return (1);
}

int	ft_strlen_nonl(char *str)
{
	int i = 0;

	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

int	check_rectangular(t_map *map)
{
	int initial_len = 0;
	int i;
	int actual_len;

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
	int i;
	int j;
	int p;
	int e;

	i = 0;
	p = 0;
	e = 0;
	while (i < map->size.y)
	{
		j = 0;
		while (j < map->size.x)
		{
			if (map->coords[i][j] == 'P')
				p++;
			if (map->coords[i][j] == 'E')
				e++;
			if (map->coords[i][j] == 'C')
				map->total_collec++;
			j++;
		}
		i++;
	}
	if (p != 1 || e != 1 || map->total_collec == 0)
		return (0);
	return (1);
}

int fill(t_map *map, t_vector size, t_vector p_pos, int *c)
{
    // Verifica si p_pos está fuera de los límites del mapa
    if (p_pos.x < 0 || p_pos.y < 0 || p_pos.x >= size.x || p_pos.y >= size.y)
        return 0;

    // Verifica si p_pos es una casilla válida
    char current_cell = map->coords[p_pos.y][p_pos.x];
    if (current_cell == 'C')
	{
        (*c)++;
		map->coords[p_pos.y][p_pos.x] = '0';
	}
    else if (current_cell == '1')
        return 0;
	else if (current_cell == 'E')
		return (*c == map->total_collec) ? 1 : 0;

    // Marca la casilla actual como visitada
    map->coords[p_pos.y][p_pos.x] = '1';

    // Realiza la llamada recursiva en las cuatro direcciones posibles
    if (fill(map, size, (t_vector){p_pos.x - 1, p_pos.y}, c) ||
        fill(map, size, (t_vector){p_pos.x + 1, p_pos.y}, c) ||
        fill(map, size, (t_vector){p_pos.x, p_pos.y - 1}, c) ||
        fill(map, size, (t_vector){p_pos.x, p_pos.y + 1}, c))
    {
        return 1; // Hay un camino válido
    }

    return 0; // No hay camino válido
}


int	valid_path(t_game *game)
{
	int	p_x = game->collection.player.pos.x;
	int	p_y = game->collection.player.pos.y;

	t_map	map_copy = copy_map(&game->map);

	int	valid_c = 0;
	if (!fill(&map_copy, (t_vector){game->map.size.x, game->map.size.y}, 
		(t_vector){p_x, p_y}, &valid_c))
	{
		free_map(&map_copy);
		return (0);
	}
	free_map(&map_copy);
	return (1);
}

int	valid_map(t_game *game)
{
	int y;
	int x;

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
		return(error("map has to have 1 P, 1 E and at least 1 C"));
	if (!valid_path(game))
		return (error("the map doesn't have a valid path"));
	return (1);
}
