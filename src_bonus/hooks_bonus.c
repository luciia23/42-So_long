/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:07:48 by lcollado          #+#    #+#             */
/*   Updated: 2024/01/09 21:43:52 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

int	on_key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == ARROW_UP)
	{
		game->actions.key_up = true;
		update(game);
	}
	else if (keycode == KEY_S || keycode == ARROW_DOWN)
	{
		game->actions.key_down = true;
		update(game);
	}
	else if (keycode == KEY_A || keycode == ARROW_LEFT)
	{
		game->actions.key_left = true;
		update(game);
	}
	else if (keycode == KEY_D || keycode == ARROW_RIGHT)
	{
		game->actions.key_right = true;
		update(game);
	}
	else if (keycode == ESC)
		exit(0);
	return (0);
}

int	on_key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == ARROW_UP)
		game->actions.key_up = false;
	else if (keycode == KEY_S || keycode == ARROW_DOWN)
		game->actions.key_down = false;
	else if (keycode == KEY_A || keycode == ARROW_LEFT)
		game->actions.key_left = false;
	else if (keycode == KEY_D || keycode == ARROW_RIGHT)
		game->actions.key_right = false;
	return (0);
}

void	verify(int x, int y, t_game *game)
{
	if (game->map.coords[y][x] == 'C')
	{
		game->map.coords[y][x] = '0';
		game->player.collec++;
		if (game->player.collec == game->map.total_collec)
		{
			if (game->collection.exit.img_ptr)
				mlx_destroy_image(game->mlx, game->collection.exit.img_ptr);
			game->collection.exit.img_ptr = mlx_xpm_file_to_image(game->mlx,
					OPEN_EXIT_IMG, (int *)&game->collection.exit.size.x,
					(int *)&game->collection.exit.size.y);
		}
	}
	else if (game->map.coords[y][x] == 'D')
		lose_game(game);
	else if ((game->map.coords[y][x] == 'E'
		&& game->player.collec == game->map.total_collec))
		win_game(game);
}

void	check_collision(t_game *game)
{
	t_enemy	*current;
	
	current = game->enemies;
	while (current)
	{
		if (game->player.pos.x == current->sprite.pos.x
			&& game->player.pos.y == current->sprite.pos.y)
		{
			lose_game(game);
			return ;
		}
		current = current->next;
	}
}

int	update(t_game *game)
{
	move_enemies(game, game->enemies);
	check_frames(game);
	check_collision(game);
	if (game->actions.key_right)
		move_player_if_possible(game, 1, 0, game->player.right);
	else if (game->actions.key_left)
		move_player_if_possible(game, -1, 0, game->player.left);
	else if (game->actions.key_up)
		move_player_if_possible(game, 0, -1, game->player.back);
	else if (game->actions.key_down)
		move_player_if_possible(game, 0, 1, game->player.front);
	return (0);
}
