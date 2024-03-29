/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:03:26 by lcollado          #+#    #+#             */
/*   Updated: 2024/02/11 17:25:35 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

t_image	new_file_img(void *mlx, char *path)
{
	t_image	image;

	image.img_ptr = mlx_xpm_file_to_image(mlx, path, (int *)&image.size.x,
			(int *)&image.size.y);
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

void	set_anim(t_game *game)
{
	game->player.right = (t_image *)malloc(sizeof(t_image) * 3);
	game->player.right[0] = new_file_img(game->mlx, LINK_RIGHT1);
	game->player.right[1] = new_file_img(game->mlx, LINK_RIGHT2);
	game->player.right[2] = new_file_img(game->mlx, LINK_RIGHT3);
	game->player.left = (t_image *)malloc(sizeof(t_image) * 3);
	game->player.left[0] = new_file_img(game->mlx, LINK_LEFT1);
	game->player.left[1] = new_file_img(game->mlx, LINK_LEFT2);
	game->player.left[2] = new_file_img(game->mlx, LINK_LEFT3);
	game->player.front = (t_image *)malloc(sizeof(t_image) * 3);
	game->player.front[0] = new_file_img(game->mlx, LINK_FRONT1);
	game->player.front[1] = new_file_img(game->mlx, LINK_FRONT2);
	game->player.front[2] = new_file_img(game->mlx, LINK_FRONT3);
	game->player.back = (t_image *)malloc(sizeof(t_image) * 3);
	game->player.back[0] = new_file_img(game->mlx, LINK_BACK1);
	game->player.back[1] = new_file_img(game->mlx, LINK_BACK2);
	game->player.back[2] = new_file_img(game->mlx, LINK_BACK3);
}

void	init_img(t_game *game)
{
	game->collection.coin = new_file_img(game->mlx, COIN_IMG);
	game->collection.exit = new_file_img(game->mlx, EXIT_IMG);
	game->collection.open_exit = new_file_img(game->mlx, OPEN_EXIT_IMG);
	game->collection.floor = new_file_img(game->mlx, FLOOR_IMG);
	game->collection.wall = new_file_img(game->mlx, TREE_IMG);
	set_anim(game);
	game->collection.panel = load_panel_font(game);
}

void	draw_img(t_game *game, int x, int y, int flag)
{
	if (game->map.coords[y][x] == '1' || game->map.coords[y][x] == 'E'
	|| game->map.coords[y][x] == 'C' || game->map.coords[y][x] == 'P'
		|| game->map.coords[y][x] == 'D')
		mlx_put_image_to_window(game->mlx, game->window.win,
			game->collection.floor.img_ptr, x * TILE_SIZE, y * TILE_SIZE);
	if (game->map.coords[y][x] == '1')
		mlx_put_image_to_window(game->mlx, game->window.win,
			game->collection.wall.img_ptr, x * TILE_SIZE, y * TILE_SIZE);
	else if (flag == 1 && game->map.coords[y][x] == 'P')
		mlx_put_image_to_window(game->mlx, game->window.win,
			game->player.front[1].img_ptr, x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map.coords[y][x] == 'C')
		mlx_put_image_to_window(game->mlx, game->window.win,
			game->collection.coin.img_ptr, x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map.coords[y][x] == 'E')
		mlx_put_image_to_window(game->mlx, game->window.win,
			game->collection.exit.img_ptr, x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map.coords[y][x] == '0')
		mlx_put_image_to_window(game->mlx, game->window.win,
			game->collection.floor.img_ptr, x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map.coords[y][x] == 'D')
		mlx_put_image_to_window(game->mlx, game->window.win,
			game->enemies->sprite.img.img_ptr, x * TILE_SIZE, y * TILE_SIZE);
}
