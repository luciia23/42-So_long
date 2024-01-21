/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:41:53 by lcollado          #+#    #+#             */
/*   Updated: 2024/01/10 12:45:26 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

int	movement(t_game *game, int x, int y)
{
	int		x_pos;
	int		y_pos;
	char	sig;

	x_pos = game->player.pos.x + x;
	y_pos = game->player.pos.y + y;
	sig = game->map.coords[y_pos][x_pos];
	if (sig == '1')
		return (0);
	// if (sig != '1' && (sig != 'E'
	// 		|| (sig == 'E' && game->player.collec == game->map.total_collec)))
	// 	return (1);
	// else
	return (1);
}

void	move_player(t_game *game, int dx, int dy, t_image *image)
{
	game->player.pos.x += dx;
	game->player.pos.y += dy;
	game->player.steps++;
	verify(game->player.pos.x, game->player.pos.y, game);
	mlx_clear_window(game->mlx, game->window.win);
	draw_map(game, 0);
	mlx_put_image_to_window(game->mlx, game->window.win,
		image[game->player.current_frame].img_ptr,
		game->player.pos.x * TILE_SIZE, game->player.pos.y * TILE_SIZE);
}

void	move_player_if_possible(t_game *game, int dx, int dy, t_image *sprite)
{
	if (movement(game, dx, dy))
		move_player(game, dx, dy, sprite);
	else
		draw_player(game, sprite);
}
