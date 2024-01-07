/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:43:20 by lcollado          #+#    #+#             */
/*   Updated: 2023/12/28 12:51:02 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

void	check_frames(t_game *game)
{
	if (game->player.current_frame >= 2)
		game->player.current_frame = 0;
	else
		game->player.current_frame++;
}

void	draw_enemy(t_game *game, int x, int y, t_enemy *enemy)
{
	int	e_x;
	int	e_y;

	e_x = enemy->sprite.pos.x + x;
	e_y = enemy->sprite.pos.y + y;
	game->map.coords[enemy->sprite.pos.y][enemy->sprite.pos.x] = '0';
	game->map.coords[e_y][e_x] = 'D';
}

void	draw_player(t_game *game, t_image *image)
{
	mlx_clear_window(game->mlx, game->window.win);
	draw_map(game, 0);
	mlx_put_image_to_window(game->mlx, game->window.win,
		image[game->player.current_frame].img_ptr,
		game->player.pos.x * TILE_SIZE, game->player.pos.y * TILE_SIZE);
}
