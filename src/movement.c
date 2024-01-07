/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 21:56:46 by lcollado          #+#    #+#             */
/*   Updated: 2024/01/07 22:00:06 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	is_valid_move(t_game *game, int x, int y)
{
	char	sig;

	sig = game->map.coords[y][x];
	if (x < 0 || x >= game->map.size.x || y < 0 || y >= game->map.size.y)
		return (0);
	if (sig == '1')
		return (0);
	if (sig == 'E' && game->collec != game->map.total_collec)
		return (0);
	return (1);
}

void	move_player(t_game *game, int x, int y)
{
	game->moving = 1;
	game->movements++;
	print_steps(game);
	game->collection.player.pos.x = x;
	game->collection.player.pos.y = y;
}

void	movement_verification(t_game *game, int new_x, int new_y)
{
	if (is_valid_move(game, new_x, new_y))
	{
		move_player(game, new_x, new_y);
		verify_collec(new_x, new_y, game);
	}
}
