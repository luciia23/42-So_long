/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:03:27 by lcollado          #+#    #+#             */
/*   Updated: 2023/12/20 12:53:06 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	ft_input(int key, t_game *game);

int	g_allowed_keys[] = {ARROW_RIGHT, ARROW_LEFT, ARROW_DOWN, ARROW_UP, KEY_A, KEY_D, KEY_S, KEY_W};
int	g_allowed_keys_count = sizeof(allowed_keys) / sizeof(allowed_keys[0]);

int	array_contains(int *array, int size, int key)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (array[i] == key)
			return (1);
		i++;
	}
	return (0);
}

int	on_key_press(int keycode, t_game *game)
{
	if (array_contains(allowed_keys, allowed_keys_count, keycode))
		ft_input(keycode, game);
	else if (keycode == ESC)
		exit(0);
	return (0);
}

int	on_key_release(int keycode, t_game *game)
{
	if (array_contains(allowed_keys, allowed_keys_count, keycode))
		game->moving = 0;
	return (0);
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
		printf("THE END");
		mlx_destroy_window(game->mlx, game->window.win);
		exit(0);
	}
}

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

int	ft_input(int key, t_game *game)
{
	int	pos_x;
	int	pos_y;
	int	new_x;
	int	new_y;
	
	pos_x = game->collection.player.pos.x;
	pos_y = game->collection.player.pos.y;
	new_x = pos_x;
	new_y = pos_y;
	if (key == ARROW_RIGHT || key == KEY_D)
		new_x = pos_x + 1;
	else if (key == ARROW_LEFT || key == KEY_A)
		new_x = pos_x - 1;
	else if (key == ARROW_DOWN || key == KEY_S)
		new_y = pos_y + 1;
	else if (key == ARROW_UP || key == KEY_W)
		new_y = pos_y - 1;
	movement_verification(game, new_x, new_y);
	mlx_clear_window(game->mlx, game->window.win);
	draw_map(game);
	mlx_put_image_to_window(game->mlx, game->window.win,
		game->collection.player.img.img_ptr,
		game->collection.player.pos.x * TILE_SIZE,
		game->collection.player.pos.y * TILE_SIZE);
	return (0);
}
