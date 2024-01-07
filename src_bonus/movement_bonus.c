/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:41:53 by lcollado          #+#    #+#             */
/*   Updated: 2023/12/28 12:52:29 by lcollado         ###   ########.fr       */
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
	if (sig != '1' && (sig != 'E'
			|| (sig == 'E' && game->player.collec == game->map.total_collec)))
		return (1);
	else
		return (0);
}

int	enemy_movement(t_game *game, int x, int y, t_enemy *enemy)
{
	int		x_pos;
	int		y_pos;
	char	sig;

	x_pos = enemy->sprite.pos.x + x;
	y_pos = enemy->sprite.pos.y + y;
	sig = game->map.coords[y_pos][x_pos];
	if (sig == '0')
	{
		enemy->sprite.pos.x = x_pos;
		enemy->sprite.pos.y = y_pos;
		return (1);
	}
	else
		return (0);
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

void	move_enemy(t_game *game, t_enemy *enemy)
{
	int	r;
	int	dx;
	int	dy;
	int	new_x;
	int	new_y;

	r = rand() % 4;
	dx = 0;
	dy = 0;
	if (r == 0)
		dx = 1;
	else if (r == 1)
		dy = -1;
	else if (r == 2)
		dx = -1;
	else if (r == 3)
		dy = 1;
	new_x = enemy->sprite.pos.x + dx;
	new_y = enemy->sprite.pos.y + dy;
	if (enemy_movement(game, dx, dy, enemy))
	{
		game->map.coords[enemy->sprite.pos.y - dy][enemy->sprite.pos.x - dx] = '0';
		enemy->sprite.pos.x = new_x;
		enemy->sprite.pos.y = new_y;
		game->map.coords[enemy->sprite.pos.y][enemy->sprite.pos.x] = 'D';
		draw_map(game, 0);
	}
}

void	move_enemies(t_game *game, t_enemy *enemies)
{
	t_enemy	*current;
	int		i;
	
	current = enemies;
	i = 0;
	while (current && i < game->enemy_count)
	{
		move_enemy(game, current);
		i++;
		current = current->next;
	}
}
