#include "game.h"

void    img_init(t_game *game)
{
    game->collection.floor = new_file_img(game->mlx, FLOOR_IMG);
    game->collection.wall = new_file_img(game->mlx, TREE_IMG);
    game->collection.exit = new_file_img(game->mlx, EXIT_IMG);
    game->collection.player = new_sprite(game->mlx, LINK_IMG);
    game->collection.coin = new_file_img(game->mlx, COIN_IMG);
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
