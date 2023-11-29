/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:37:10 by lcollado          #+#    #+#             */
/*   Updated: 2023/11/29 15:24:13 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

int	fill(t_map *map, t_vector size, t_vector p_pos, int *c)
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
	// else if (current_cell == 'E')
	// 	return (*c == map->total_collec) ? 1 : 0;

	// Marca la casilla actual como visitada
	map->coords[p_pos.y][p_pos.x] = '1';
	// Realiza la llamada recursiva en las cuatro direcciones posibles
	fill(map, size, (t_vector){p_pos.x - 1, p_pos.y}, c);
	fill(map, size, (t_vector){p_pos.x + 1, p_pos.y}, c);
	fill(map, size, (t_vector){p_pos.x, p_pos.y - 1}, c);
	fill(map, size, (t_vector){p_pos.x, p_pos.y + 1}, c);
	if (*c == map->total_collec)
		return (1);
	return 0; // Hay un camino válido 
}


int	valid_path(t_game *game)
{
	int	p_x = game->player.pos.x;
	int	p_y = game->player.pos.y;

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