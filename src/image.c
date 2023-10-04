/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:03:48 by lcollado          #+#    #+#             */
/*   Updated: 2023/10/04 14:03:52 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

t_image	new_file_img(void *mlx, char *path) {
	t_image image;

    image.img_ptr = mlx_xpm_file_to_image(mlx, path, (int *)&image.size.x, (int *)&image.size.y);
    if (!image.img_ptr)
		printf("File could not be read%s\n", path);

	// image.img_ptr = mlx_xpm_file_to_image(mlx, path, &image.size.x, &image.size.y);
	// if (!image.img_ptr)
	// 	printf("File could not be read%s\n", path);
	// else
	// 	image.addr = mlx_get_data_addr(image.img_ptr, &(image.bpp),
	// 		&(image.line_size), &(image.endian));
	return (image);
}

t_sprite	new_sprite(void *mlx, char *file_path) {
	t_image	img;

	img = new_file_img(mlx, file_path);
	return (t_sprite){img, {img.size.x, img.size.y}};
}

void    init_player(t_game *game)
{
    int i;
    int j;
    i = 0;
    while (i < game->map.size.y)
    {
        j = 0;
        while (game->map.coords[i][j])
        {
            if (game->map.coords[i][j] == 'P')
            {
                game->collection.player.pos.x = j * TILE_SIZE;
                game->collection.player.pos.y = i * TILE_SIZE;
            }
            j++;
        }
        i++;
    }
}

void    img_init(t_game *game)
{
    game->collection.floor = new_file_img(game->mlx, FLOOR_IMG);
    game->collection.wall = new_file_img(game->mlx, TREE_IMG);
    game->collection.exit = new_file_img(game->mlx, EXIT_IMG);
    game->collection.player  = new_sprite(game->mlx, LINK_IMG);
    game->collection.coin = new_file_img(game->mlx, COIN_IMG);
    game->collec = 0;
    game->movements = 0;
    init_player(game);
}

void    draw_img(t_game *game, int x, int y)
{
    mlx_put_image_to_window(game->mlx, game->window.win, game->collection.floor.img_ptr, x *  TILE_SIZE, y * TILE_SIZE);
    if (game->map.coords[y][x] == '1')
        mlx_put_image_to_window(game->mlx, game->window.win, game->collection.wall.img_ptr, x * TILE_SIZE, y * TILE_SIZE);
    else if (game->map.coords[y][x] == 'P')
        mlx_put_image_to_window(game->mlx, game->window.win, game->collection.player.img.img_ptr, game->collection.player.pos.x, game->collection.player.pos.y);
    else if (game->map.coords[y][x] == 'C')
        mlx_put_image_to_window(game->mlx, game->window.win,game->collection.coin.img_ptr, x * TILE_SIZE, y * TILE_SIZE);
    else if (game->map.coords[y][x] == 'E')
        mlx_put_image_to_window(game->mlx,game->window.win, game->collection.exit.img_ptr, x * TILE_SIZE, y * TILE_SIZE);
    else if (game->map.coords[y][x] == '0')
        mlx_put_image_to_window(game->mlx, game->window.win, game->collection.floor.img_ptr, x * TILE_SIZE, y * TILE_SIZE);
}
