#include "game.h"

int direction;

void	select_option(t_game *game)
{
    direction = 0;
	if (game->arrow_position == ARROW_UP)
		reset_game(game);
	else if (game->arrow_position == ARROW_DOWN)
		end_game(game);
}

void	put_arrows(t_game *game)
{
	int	x;
	int	y;

	x = ((TILE_SIZE * game->map.size.x) / 2) - (150);
	y = ((TILE_SIZE * game->map.size.y) / 2);
    put_img_to_img(game->collection.total_bg, game->collection.restart, x ,y);
    put_img_to_img(game->collection.total_bg, game->collection.exit, x ,y + 128);
	if (direction == ARROW_UP)
	{
        put_img_to_img(game->collection.total_bg, game->collection.arrow_up, x - 160, y - 48);
		game->arrow_position = ARROW_UP;
	}
	else if (direction == ARROW_DOWN)
	{
        put_img_to_img(game->collection.total_bg, game->collection.arrow_down, x - 160, y + 86);
		game->arrow_position = ARROW_DOWN;
	}
    mlx_put_image_to_window(game->mlx, game->window.win, game->collection.total_bg.img_ptr, 0, 0);
}


int restart_game(int key, t_game *game)
{
    if (key == ARROW_DOWN || key == ARROW_UP || key == ENTER)
        direction = key;
    if(ARROW_UP == direction)
        put_arrows(game);
    if (ARROW_DOWN == direction)
        put_arrows(game);
    if (ENTER == direction)
        select_option(game);
    if (key == ESC && !game->options.end_failed && !game->options.end_won)
        resume_game(game);
    return 0;
}

int    game_over(t_game *game)
{
    int x;
    int y;

    x = ((TILE_SIZE * game->map.size.x) / 4);
    y = ((TILE_SIZE * game->map.size.y) / 4);
    if (game->collection.total_bg.img_ptr != NULL){
        destroy_image(game->collection.total_bg, game->mlx);
        game->collection.total_bg = new_file_img(BG_TOTAL, game->mlx);
    }
    if (game->options.end_won)
        put_img_to_img(game->collection.total_bg, game->collection.won, x, y);
    if (game->options.end_failed)
        put_img_to_img(game->collection.total_bg, game->collection.game_over, x, y);
    put_arrows(game);
    mlx_key_hook(game->window.win, restart_game, game);
    return 0;
}