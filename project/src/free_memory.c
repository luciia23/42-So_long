#include "game.h"

void free_sprite(t_sprite *sprite) {
    // free(sprite->file_path);
    // free(sprite->name);
    sprite->animations = NULL;
    sprite->name = NULL;
    sprite->file_path = NULL;
    sprite->img.img_ptr = NULL;
    sprite->dimensions.x = 0;
    sprite->dimensions.y = 0;
    sprite->dimensions.z = 0;
    sprite->pos.x = 0;
    sprite->pos.y = 0;
    sprite->pos.z = 0;
    sprite->collec = 0;
}

void    free_sprites(t_game *game)
{
    mlx_destroy_image(game->mlx, game->collection.bg.img_ptr);
    mlx_destroy_image(game->mlx, game->collection.bg_down.img_ptr);
    free_sprite(&game->collection.enemy2);
    free_sprite(&game->collection.coin);
    free_sprite(&game->collection.enemy1);
    free_sprite(&game->collection.player_one);
    free_score(game);
}

void    free_music(t_game *game)
{
    game->music.music = 0;
    game->music.coin_sound = 0;
    game->music.door_sound = 0;
    game->music.game_over_sound = 0;
    game->music.victory_sound = 0;
}


void free_map(char **coords)
{
    int i = 0;
    if (!coords)
        return;

    while (i < 11)
    {
        free(coords[i]);
        // coords[i] = NULL;
        i++;
    }
    free(coords);
}


void free_maps(t_game *game)
{
    int i;

    i = 0;
    while (i < NUM_MAPS)
    {
        free_map(game->maps[i].coords);
        i++;
    }

    game->map.size.x = 0;
    game->map.size.y = 0;
    game->map.total_collec = 0;
    mlx_destroy_image(game->mlx, game->collection.bg.img_ptr);
}