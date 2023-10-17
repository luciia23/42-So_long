/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:40:45 by lcollado          #+#    #+#             */
/*   Updated: 2023/10/10 11:12:41 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

int	error(char *msg)
{
	printf("\033[0;31m" " Error\n    %s\n" "\033[0m", msg);
	return (0);
}

void    free_map(t_map *map)
{
    int i = 0;

    while (i < map->size.y)
    {
        if (map->coords[i] != NULL)
            free(map->coords[i]);
        i++;
    }
    free(map->coords);
    map->coords = NULL;
}