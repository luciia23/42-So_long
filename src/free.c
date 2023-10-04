/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:03:15 by lcollado          #+#    #+#             */
/*   Updated: 2023/10/04 14:03:18 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

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