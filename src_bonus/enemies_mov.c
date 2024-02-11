/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_mov.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:14:45 by lcollado          #+#    #+#             */
/*   Updated: 2024/02/11 16:58:23 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

int	move_possible(t_game *game, int x, int y, t_enemy *enemy)
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

void	enemy_movement(t_game *game, t_vector d, t_enemy *enemy)
{
	int	x;
	int	y;

	if (move_possible(game, d.x, d.y, enemy))
	{
		y = enemy->sprite.pos.y - d.y;
		x = enemy->sprite.pos.x - d.x;
		game->map.coords[y][x] = '0';
		game->map.coords[enemy->sprite.pos.y][enemy->sprite.pos.x] = 'D';
		draw_map(game, 0);
	}
}

t_vector	calculate_new_position(int random)
{
	t_vector	d;

	d.x = 0;
	d.y = 0;
	if (random == 0)
		d.x = 1;
	else if (random == 1)
		d.y = -1;
	else if (random == 2)
		d.x = -1;
	else if (random == 3)
		d.y = 1;
	return (d);
}

void	move_enemy(t_game *game, t_enemy *enemy)
{
	int			random;
	t_vector	d;

	random = rand() % 4;
	d = calculate_new_position(random);
	enemy_movement(game, d, enemy);
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
