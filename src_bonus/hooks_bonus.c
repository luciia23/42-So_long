/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:07:48 by lcollado          #+#    #+#             */
/*   Updated: 2023/10/17 16:33:35 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

int allowed_keys[] = {ARROW_RIGHT, ARROW_LEFT, ARROW_DOWN, ARROW_UP, KEY_A, KEY_D, KEY_S, KEY_W};
int allowed_keys_count = sizeof(allowed_keys) / sizeof(allowed_keys[0]);

int array_contains(int *array, int size, int key) {
	int i = 0;
	while (i < size) {
		if (array[i] == key) {
			return 1;
		}
		i++;
	}
	return 0;
}

int on_key_press(int keycode, t_game *game)
{
	// printf("%d\n", keycode);
	if (keycode == KEY_W || keycode == ARROW_UP)
		game->actions.key_up = true;
	else if (keycode == KEY_S || keycode == ARROW_DOWN)
		game->actions.key_down = true;
	else if (keycode == KEY_A || keycode == ARROW_LEFT)
		game->actions.key_left = true;
	else if (keycode == KEY_D || keycode == ARROW_RIGHT)
	{
		game->actions.key_right = true;
		update(game);
	}
	else if (keycode == ESC)
		exit(0);
	return (0);
}

int on_key_release(int keycode, t_game *game)
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

// void draw(t_game *game)
// {
// 	int pos_x = game->player.pos.x;
// 	int pos_y = game->player.pos.y;
// 	char    sig;
// 	if (game->player.moving)
// 	{
// 		sig = game->map.coords[pos_y][pos_x + 1];
// 		if (sig != '1')
// 		{
// 			// Borra la ventana antes de dibujar la nueva imagen

// 		}
// 	}
// 	// draw_map(game);
// }

void	check_frames(t_game *game)
{
	if (game->player.current_frame >= 2)
		game->player.current_frame = 0;
	else
		game->player.current_frame++;
}

int	movement(t_game *game, int x, int y)
{
	int	x_pos;
	int	y_pos;
	char sig;

	x_pos = game->player.pos.x + x;
	y_pos = game->player.pos.y + y;

	sig = game->map.coords[y_pos][x_pos];
	if (sig != '1' && (sig != 'E' || ( sig == 'E' && game->player.collec == game->map.total_collec)))
		return (1);
	else
		return (0);
}

void	make_d(t_game *game)
{
	game->player.pos.x += 1;
	mlx_clear_window(game->mlx, game->window.win);
	mlx_put_image_to_window(game->mlx, game->window.win, game->collection.floor.img_ptr, game->player.pos.x * TILE_SIZE, game->player.pos.y * TILE_SIZE);
	mlx_put_image_to_window(game->mlx, game->window.win, game->player.right[game->player.current_frame].img_ptr, game->player.pos.x * TILE_SIZE, game->player.pos.y * TILE_SIZE);
}


int update(t_game *game)
{
	game->player.moving = 1;
	check_frames(game);
	if (game->actions.key_right)
	{
		if (movement(game, 1, 0))
		{
			game->player.steps++;
			make_d(game);	
		}
	}
	else if (game->actions.key_left)
	{
		if (movement(game, 1, 0))
		{
			game->player.steps++;
			make_d(game);	
		}
	}
	else if (game->actions.key_up)
	{
		if (movement(game, 1, 0))
		{
			game->player.steps++;
			make_d(game);	
		}
	}
	else if (game->actions.key_down)
	{
		if (movement(game, 1, 0))
		{
			game->player.steps++;
			make_d(game);	
		}
		
	}
	return (0);
}