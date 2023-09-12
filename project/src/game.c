# include "game.h"

void    new_game(t_game *game)
{
    if(game->options.end_failed == 1 || game->options.end_won == 1)
    {
        game->options.end_failed = 0;
        game->options.end_won = 0;
        togglePlay();
    }
    map_init(game);
    game->collection.bg = new_img(game->map.size.x * TILE_SIZE, game->map.size.y * TILE_SIZE, game->mlx);
    search_sprite(game);
    search_enemy(game);
    search_enemy2(game);
    resume_game(game);
}

void    reset_actions(t_game *game)
{
    game->actions.key_up = 0;
    game->actions.key_down = 0;
    game->actions.key_right = 0;
    game->actions.key_left = 0;
}

void    reset_directions(t_game *game)
{
    game->directions.east = 0;
    game->directions.west = 0;
    game->directions.up = 0;
    game->directions.down = 0;
}

void    reset_movements(t_game *game)
{
    game->moving = 0;
    game->moving_enemy1 = 0;
    game->moving_enemy2 = 0;
}

void    resume_game(t_game *game)
{
    reset_actions(game);
    reset_directions(game);
    reset_movements(game);
    mlx_hook(game->window.win, 2, 1L<<0, on_key_press, game);
	mlx_hook(game->window.win, 3, 1L<<1, on_key_release, game);
    mlx_loop_hook(game->mlx, update, game);
    mlx_loop(game->mlx);
}


int end_game(t_game *game)
{
    (void)game;
    // printf("end game!\n");
    // // free_maps(game);
    // free_sprites(game);
    // destroy_sprite(game->collection.enemy1, game->mlx);
    // destroy_sprite(game->collection.player_one, game->mlx);
    // mlx_clear_window(game->mlx, game->window.win);
    // mlx_destroy_window(game->mlx, game->window.win);
    // mlx_destroy_display(game->mlx);
    // free_music(game);
    // // quit(&game->vars_sound);
    // // quitMixer(&game->vars_sound);
    // free(game->mlx);
    exit(0);
    return (0);
}

void    reset_game(t_game *game)
{
    reset_actions(game);
    reset_directions(game);
    reset_movements(game);
    mlx_clear_window(game->mlx, game->window.win);
    game->current_map = 0;
    game->collec = 0;
    free_maps(game);
    new_game(game);
}