#include "game.h"


void	put_img_to_img(t_image dst, t_image src, int x, int y);

void draw_island(t_game *game, t_image *moneda,int x, int y, char pos)
{
	if (pos == '0' || pos == 'P' || pos == 'C' || pos == 'D' || pos == 'S')
		put_img_to_img(game->collection.bg, game->collection.island.sand, x, y);
	if (pos == 'U')
		put_img_to_img(game->collection.bg, game->collection.island.top, x, y);
	if (pos == 'L')
		put_img_to_img(game->collection.bg, game->collection.island.left, x, y);
	if (pos == 'R' || pos == 'E')
		put_img_to_img(game->collection.bg, game->collection.island.right, x, y);
	if (pos == 'B')
		put_img_to_img(game->collection.bg, game->collection.island.bottom, x, y);
	if (pos == '1')
		put_img_to_img(game->collection.bg, game->collection.island.water, x, y);
	if (pos == 'C')
		put_img_to_img(game->collection.bg, *moneda, x, y);
	if (pos == 'S')
		put_img_to_img(game->collection.bg, game->collection.island.star, x, y);
	if (pos == 'E' && game->collec == game->map.total_collec)
		put_img_to_img(game->collection.bg, game->collection.island.boat, x, y);
	if (pos == 'K')
		put_img_to_img(game->collection.bg, game->collection.island.k_curve, x, y);
	if (pos == 'W')
		put_img_to_img(game->collection.bg, game->collection.island.w_curve, x, y);
	if (pos == 'A')
		put_img_to_img(game->collection.bg, game->collection.island.a_curve, x, y);
	if (pos == 'J')
		put_img_to_img(game->collection.bg, game->collection.island.j_curve, x, y);
}

void draw_fild(t_game *game, t_image *moneda,int x, int y, char pos)
{
	if (pos == '0' || pos == 'P' || pos == 'C' || pos == 'D' || pos == 'B' || pos == 'E' || pos == 'S' || pos == 'R')
		put_img_to_img(game->collection.bg, game->collection.field.floor, x, y);
	if (pos == '1')
		put_img_to_img(game->collection.bg, game->collection.field.bush, x, y);
	if (pos == 'B')
		put_img_to_img(game->collection.bg, game->collection.field.flower_blue, x, y);
	if (pos == 'S')
		put_img_to_img(game->collection.bg, game->collection.field.flower_star, x, y);
	if (pos == 'R')
		put_img_to_img(game->collection.bg, game->collection.field.flower_red, x, y);
	if (pos == 'E' && game->collec != game->map.total_collec)
		put_img_to_img(game->collection.bg, game->collection.field.rock, x, y);
	else if (pos == 'E')
		put_img_to_img(game->collection.bg, game->collection.field.ladder, x, y);
	if (pos == 'C')
		put_img_to_img(game->collection.bg, *moneda, x, y);
}

void draw_forest(t_game *game, t_image *moneda,int x, int y, char pos)
{
	if (pos == '0' || pos == 'P' || pos == 'C' || pos == 'D' || pos == 'd' || pos == 'E' || pos == 'S' || pos == '1')
		put_img_to_img(game->collection.bg, game->collection.forest.floor, x, y);
	if (pos == '1')
		put_img_to_img(game->collection.bg, game->collection.forest.tree, x, y);
	if (pos == 'S')
		put_img_to_img(game->collection.bg, game->collection.forest.mushroom, x, y);
	if (pos == 'E' && game->collec != game->map.total_collec)
		put_img_to_img(game->collection.bg, game->collection.field.rock, x, y);
	else if (pos == 'E')
		put_img_to_img(game->collection.bg, game->collection.field.ladder, x, y);
	if (pos == 'C')
		put_img_to_img(game->collection.bg, *moneda, x, y);
}

void draw_castle(t_game *game, t_image *moneda,int x, int y, char pos)
{
	if (pos == '0' || pos == 'A' || pos == 'P' || pos == 'C' || pos == 'D' || pos == 'd' || pos == 'E')
		put_img_to_img(game->collection.bg, game->collection.castle.floor, x, y);
	if (pos == '1' || pos == 'T')
		put_img_to_img(game->collection.bg, game->collection.castle.wall_top, x, y);
	if (pos == 'T')
		put_img_to_img(game->collection.bg, game->collection.castle.torch, x, y);
	if (pos == 'A')
		put_img_to_img(game->collection.bg, game->collection.castle.candle, x, y);
	if (pos == '2')
		put_img_to_img(game->collection.bg, game->collection.castle.infill_wall, x, y);
	if (pos == '3')
		put_img_to_img(game->collection.bg, game->collection.castle.wall_bottom, x, y);
	if (pos == 'E' && game->collec != game->map.total_collec)
		put_img_to_img(game->collection.bg, game->collection.castle.hatch, x, y);
	else if (pos == 'E')
		put_img_to_img(game->collection.bg, game->collection.castle.ladder, x, y);
	if (pos == 'C')
		put_img_to_img(game->collection.bg, *moneda, x, y);
}

void draw_img(t_game *game, t_image *moneda,int x, int y)
{
	char	pos = game->map.coords[y][x];
	int		pos_x = x * TILE_SIZE;
	int		pos_y = y * TILE_SIZE;
	if (game->current_map == 0)
		draw_island(game, moneda, pos_x, pos_y, pos);
	else if (game->current_map == 1)
		draw_fild(game, moneda, pos_x, pos_y, pos);
	else if (game->current_map == 2)
		draw_forest(game, moneda, pos_x, pos_y, pos);
	else if (game->current_map == 3)
		draw_castle(game, moneda, pos_x, pos_y, pos);
	
	if (pos == 'D' || pos == 'd')
		game->count_enemy++;
}

t_image	new_img(int w, int h, void *mlx)
{
	t_image	image;

	image.img_ptr = mlx_new_image(mlx, w, h);
	image.addr = mlx_get_data_addr(image.img_ptr, &(image.bpp),
			&(image.line_size), &(image.endian));
	image.size.x = w;
	image.size.y = h;
	return (image);
}

t_image	new_file_img(char * path,  void *mlx) {
	t_image image;

	image.img_ptr = mlx_xpm_file_to_image(mlx, path, &image.size.x, &image.size.y);
	if (!image.img_ptr)
		printf("File could not be read%s\n", path);
	else
		image.addr = mlx_get_data_addr(image.img_ptr, &(image.bpp),
			&(image.line_size), &(image.endian));
	return (image);
}

void	put_pixel_img(t_image img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
		return ;

	if (x >= 0 && y >= 0 && x < img.size.x && y < img.size.y) {
		dst = img.addr + (y * img.line_size + x * (img.bpp / 8));
		*(unsigned int *) dst = color;
	}
}

unsigned int	get_pixel_img(t_image img, int x, int y)
{
	return (*(unsigned int *)((img.addr
			+ (y * img.line_size) + (x * img.bpp / 8))));
}

static int	put_pixel_valid(t_image img, int x, int y) {
	if (x >= 0 && y >= 0 && x < img.size.x && y < img.size.y) {
		return (*(unsigned int *)(img.addr + (y * img.line_size + x * (img.bpp / 8))) != 0xFF000000 &&
		*(unsigned int *)(img.addr + (y * img.line_size + x * (img.bpp / 8))) != 0x00000000);
	}
	return 0;
}

void	put_img_to_img(t_image dst, t_image src, int x, int y) {
	int i;
	int j;

	i = 0;
	while(i < src.size.x) {
		j = 0;
		while (j < src.size.y) {
			if (put_pixel_valid(src, i, j))
				put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
			j++;
		}
		i++;
	}
}

void remove_img_from_img(t_image dst, t_image src, int x, int y) {
    int i;
    int j;

    i = 0;
    while (i < src.size.x) {
        j = 0;
        while (j < src.size.y) {
            if (put_pixel_valid(src, i, j)) {
                put_pixel_img(dst, x + i, y + j, 0x00000000); // Establecer el color a transparente
            }
            j++;
        }
        i++;
    }
}



void	destroy_image(t_image img, void *mlx) {
	if (img.img_ptr && mlx) 
       mlx_destroy_image(mlx, img.img_ptr);
}