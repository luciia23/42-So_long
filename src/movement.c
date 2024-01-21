/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 21:56:46 by lcollado          #+#    #+#             */
/*   Updated: 2024/01/10 13:06:02 by lcollado         ###   ########.fr       */
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
	// if (sig == 'E' && game->collec != game->map.total_collec)
	// 	return (0);
	return (1);
}

void	verify_collec(int x, int y, t_game *game)
{
	if (game->map.coords[y][x] == 'C')
	{
		game->map.coords[y][x] = '0';
		game->collec++;
		if (game->collec == game->map.total_collec)
		{
			if (game->collection.exit.img_ptr)
				mlx_destroy_image(game->mlx, game->collection.exit.img_ptr);
			game->collection.exit.img_ptr = mlx_xpm_file_to_image(game->mlx,
					OPEN_EXIT_IMG, (int *)&game->collection.exit.size.x,
					(int *)&game->collection.exit.size.y);
		}
	}
	else if ((game->map.coords[y][x] == 'E'
		&& game->collec == game->map.total_collec))
	{
		ft_putstr_fd("THE END\n", 2);
		mlx_destroy_window(game->mlx, game->window.win);
		exit(0);
	}
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
