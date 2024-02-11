/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:40:45 by lcollado          #+#    #+#             */
/*   Updated: 2024/02/11 17:50:01 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

int	error(char *msg)
{
	ft_putstr_fd("\033[0;31m" " Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

void	win_game(t_game *game)
{
	ft_putstr_fd("\033[0;32m THE END : YOU WON \n", 1);
	mlx_destroy_window(game->mlx, game->window.win);
	exit(0);
}

void	lose_game(t_game *game)
{
	ft_putstr_fd("\033[0;31m THE END : YOU LOST \n", 1);
	mlx_destroy_window(game->mlx, game->window.win);
	exit(0);
}

int	ft_strlen_nonl(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->size.y)
	{
		if (map->coords[i] != NULL)
			free(map->coords[i]);
		i++;
	}
	free(map->coords);
	map->coords = NULL;
}
