/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:03:27 by lcollado          #+#    #+#             */
/*   Updated: 2024/01/07 22:00:32 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	ft_input(int key, t_game *game);

int	on_key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == ARROW_UP)
		ft_input(keycode, game);
	else if (keycode == KEY_S || keycode == ARROW_DOWN)
		ft_input(keycode, game);
	else if (keycode == KEY_A || keycode == ARROW_LEFT)
		ft_input(keycode, game);
	else if (keycode == KEY_D || keycode == ARROW_RIGHT)
		ft_input(keycode, game);
	else if (keycode == ESC)
		exit(0);
	return (0);
}

int	on_key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == ARROW_UP)
		game->moving = 0;
	else if (keycode == KEY_S || keycode == ARROW_DOWN)
		game->moving = 0;
	else if (keycode == KEY_A || keycode == ARROW_LEFT)
		game->moving = 0;
	else if (keycode == KEY_D || keycode == ARROW_RIGHT)
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
