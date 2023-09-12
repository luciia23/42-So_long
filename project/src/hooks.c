#include "game.h"
#include <stdint.h>
#include "sprite.h"

int on_key_press(int key, t_game *game)
{
	if (key == KEY_W || key == ARROW_UP)
		game->actions.key_up = true;
	else if (key == KEY_S || key == ARROW_DOWN)
		game->actions.key_down = true;
	else if (key == KEY_A || key == ARROW_LEFT)
		game->actions.key_left = true;
	else if (key == KEY_D || key == ARROW_RIGHT)
		game->actions.key_right = true;
	// else if (key == ESC)
	// 	mlx_loop_hook(game->mlx, game_over, game);
	else if (key == KEY_P)
		togglePlay();
	else
		return (0);
	return 0;
}

int on_key_release(int key, t_game *game)
{
	if (key == ARROW_UP || key == KEY_W)
		game->actions.key_up = false;
	else if (key == ARROW_DOWN || key == KEY_S)
		game->actions.key_down = false;
	else if (key == ARROW_LEFT || key == KEY_A)
		game->actions.key_left = false;
	else if (key == ARROW_RIGHT || key == KEY_D)
		game->actions.key_right = false;
	else if (key == ESC)
		mlx_loop_hook(game->mlx, game_over, game);
	else
		return (0);
	return 0;
}