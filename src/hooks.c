/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:03:27 by lcollado          #+#    #+#             */
/*   Updated: 2023/10/19 15:54:49 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	ft_input(int key, t_game *game);

int allowed_keys[] = {ARROW_RIGHT, ARROW_LEFT, ARROW_DOWN, ARROW_UP, KEY_A, KEY_D, KEY_S, KEY_W};
int allowed_keys_count = sizeof(allowed_keys) / sizeof(allowed_keys[0]);

int	array_contains(int *array, int size, int key) {
	int	i;

	i = 0;
	while (i < size) {
		if (array[i] == key) {
			return 1;
		}
		i++;
	}
	return 0;
}

int	on_key_press(int keycode, t_game *game)
{
	printf("%d\n", keycode);
	if (array_contains(allowed_keys, allowed_keys_count, keycode)) {
		ft_input(keycode, game);
	}
    else if (keycode == ESC)
        exit(0);
    return (0);
}

int	on_key_release(int keycode, t_game *game)
{
 	if (array_contains(allowed_keys, allowed_keys_count, keycode)) {
		game->moving = 0;
	}

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
			game->collection.exit.img_ptr = mlx_xpm_file_to_image(game->mlx, OPEN_EXIT_IMG, (int *)&game->collection.exit.size.x, (int *)&game->collection.exit.size.y);
		}
	}
	else if ((game->map.coords[y][x] == 'E' && game->collec == game->map.total_collec))
	{
		printf("THE END");
		mlx_destroy_window(game->mlx, game->window.win);
		exit(0);
	}
}

int	ft_input(int key, t_game *game)
{
	int pos_x = game->collection.player.pos.x / TILE_SIZE; 
	int pos_y = game->collection.player.pos.y / TILE_SIZE; 
	char	sig;

	if ((key == ARROW_RIGHT) || (key == KEY_D))
	{
		sig = game->map.coords[pos_y][pos_x + 1];
		if (sig != '1' && (sig != 'E' || ( sig == 'E' && game->collec == game->map.total_collec)))
		{
			game->moving = 1;
			game->movements++;
			print_steps(game);
			game->collection.player.pos.x += game->collection.player.img.size.x;
			verify_collec(pos_x + 1, pos_y, game);
		}
	}
	else if (key == ARROW_LEFT || (key == KEY_A))
	{
		sig = game->map.coords[pos_y][pos_x - 1];
		if (sig != '1' && (sig != 'E' || ( sig == 'E' && game->collec == game->map.total_collec)))
		{
			game->moving = 1;
			game->movements++;
			print_steps(game);
			game->collection.player.pos.x -= game->collection.player.img.size.x;
			verify_collec(pos_x - 1, pos_y, game);
		}
	}
	else if (key == ARROW_DOWN || (key == KEY_S))
	{
		sig = game->map.coords[pos_y + 1][pos_x];
		if (sig != '1' && (sig != 'E' || ( sig == 'E' && game->collec == game->map.total_collec)))
		{
			game->moving = 1;
			game->movements++;
			print_steps(game);
			game->collection.player.pos.y += game->collection.player.img.size.y;
			verify_collec(pos_x, pos_y + 1, game);
		}
	}
	else if (key == KEY_W || (key == ARROW_UP))
	{
		sig = game->map.coords[pos_y - 1][pos_x];
		if (sig != '1' && (sig != 'E' || ( sig == 'E' && game->collec == game->map.total_collec)))
		{
			game->moving = 1;
			game->movements++;
			print_steps(game);
			game->collection.player.pos.y -= game->collection.player.img.size.y;
			verify_collec(pos_x, pos_y - 1, game);				
		}
	}

	mlx_clear_window(game->mlx, game->window.win);
	draw_map(game);
	mlx_put_image_to_window(game->mlx, game->window.win,
		game->collection.player.img.img_ptr, game->collection.player.pos.x, game->collection.player.pos.y);
	return (0);
}