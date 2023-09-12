#include "game.h"

void    init_all(t_game *game) 
{
    game->actions = (t_actions){false, false, false, false, false, false};
    init_sound(&game->vars_sound);
    collection_init(game);
    init_slice(game);
    game_sound(game);
}

int manage_game(int key, void *param)
{
    t_game *game = (t_game *)param;

    if (key == 32) {
        game->options.start = 1;
    } else if (key == ESC) {
        exit(0);
    }
    if (game->options.start == 1)
    {
        mlx_destroy_image(game->mlx, game->collection.press.img_ptr);
        mlx_destroy_image(game->mlx, game->collection.start.img_ptr);
        init_all(game);
        new_game(game);
    }
    return 0;
}

void game_init()
{
    t_game  game;
    game.options = (t_options){0,0,0};
    game.mlx = mlx_init();
    game.window = ft_new_window(game.mlx, 960, 832, "ZELDA: THE REVENGE OF THE CHICKENS");
    game.collection.start = new_file_img(BG_TOTAL,game.mlx);
    game.collection.press = new_file_img(PRESS_IMG, game.mlx);
    put_img_to_img(game.collection.start, game.collection.press, 120, 780);
    mlx_put_image_to_window(game.mlx, game.window.win, game.collection.start.img_ptr, 0, 0);
    mlx_key_hook(game.window.win, manage_game, &game);
    mlx_loop(game.mlx);
}

int main(void)
{
    game_init();
    return 0;
}
