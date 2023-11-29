/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:03:48 by lcollado          #+#    #+#             */
/*   Updated: 2023/11/23 14:03:05 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

t_image	new_file_img(void *mlx, char *path)
{
	t_image	image;

	image.img_ptr = mlx_xpm_file_to_image(mlx, path,
			(int *)&image.size.x, (int *)&image.size.y);
	if (!image.img_ptr)
	{
		ft_putstr_fd("File could not be read: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
	}
	return (image);
}

t_sprite	new_sprite(void *mlx, char *file_path)
{
	t_image	img;

	img = new_file_img(mlx, file_path);
	return ((t_sprite){img, {img.size.x, img.size.y}});
}

void	draw_img(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->window.win,
		game->collection.floor.img_ptr, x * TILE_SIZE, y * TILE_SIZE);
	if (game->map.coords[y][x] == '1')
		mlx_put_image_to_window(game->mlx, game->window.win,
			game->collection.wall.img_ptr, x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map.coords[y][x] == 'P')
		mlx_put_image_to_window(game->mlx, game->window.win,
			game->collection.player.img.img_ptr,
			game->collection.player.pos.x * TILE_SIZE,
			game->collection.player.pos.y * TILE_SIZE);
	else if (game->map.coords[y][x] == 'C')
		mlx_put_image_to_window(game->mlx, game->window.win,
			game->collection.coin.img_ptr, x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map.coords[y][x] == 'E')
		mlx_put_image_to_window(game->mlx, game->window.win,
			game->collection.exit.img_ptr, x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map.coords[y][x] == '0')
		mlx_put_image_to_window(game->mlx, game->window.win,
			game->collection.floor.img_ptr, x * TILE_SIZE, y * TILE_SIZE);
}
