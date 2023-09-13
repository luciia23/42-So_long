#include "game.h"

t_image	new_file_img(void *mlx, char *path) {
	t_image image;

	image.img_ptr = mlx_xpm_file_to_image(mlx, path, &image.size.x, &image.size.y);
	if (!image.img_ptr)
		printf("File could not be read%s\n", path);
	else
		image.addr = mlx_get_data_addr(image.img_ptr, &(image.bpp),
			&(image.line_size), &(image.endian));
	return (image);
}

t_sprite	new_sprite(void *mlx, char * file_path) {
	t_image	img;

	img = new_file_img(file_path, mlx);
	return (t_sprite){img, {img.size.x, img.size.y}};
}

void    img_init(t_game *game)
{
    game->collection.floor = new_file_img(game->mlx, FLOOR_IMG);
    game->collection.wall = new_file_img(game->mlx, TREE_IMG);
    game->collection.exit = new_file_img(game->mlx, EXIT_IMG);
    game->collection.player = new_sprite(game->mlx, LINK_IMG);
}

void    draw_img(t_game *game, int x, int y)
{
    if (game->map.coords[y][x] == '1')
        mlx_put_image_to_window(game->mlx, game->window.win, game->collection.wall.img_ptr, x * TILE_SIZE, y * TILE_SIZE);
    else if (game->map.coords[y][x] == 'P')
        mlx_put_image_to_window(game->mlx, game->window.win, game->collection.player.img.img_ptr, x * TILE_SIZE, y * TILE_SIZE);
    else if (game->map.coords[y][x] == 'C')
        mlx_put_image_to_window(game->mlx, game->window.win,game->collection.coin.img_ptr, x * TILE_SIZE, y * TILE_SIZE);
    else if (game->map.coords[y][x] == 'E')
        mlx_put_image_to_window(game->mlx,game->window.win, game->collection.exit.img_ptr, x * TILE_SIZE, y * TILE_SIZE);
}