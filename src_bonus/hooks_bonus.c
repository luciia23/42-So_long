/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:07:48 by lcollado          #+#    #+#             */
/*   Updated: 2023/10/16 19:32:06 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

int allowed_keys[] = {ARROW_RIGHT, ARROW_LEFT, ARROW_DOWN, ARROW_UP, KEY_A, KEY_D, KEY_S, KEY_W};
int allowed_keys_count = sizeof(allowed_keys) / sizeof(allowed_keys[0]);

int array_contains(int *array, int size, int key) {
    int i = 0;
    while (i < size) {
        if (array[i] == key) {
            return 1;
        }
        i++;
    }
    return 0;
}

int on_key_press(int keycode, t_game *game)
{
	// printf("%d\n", keycode);
	if (keycode == KEY_W || keycode == ARROW_UP)
		game->actions.key_up = true;
	else if (keycode == KEY_S || keycode == ARROW_DOWN)
		game->actions.key_down = true;
	else if (keycode == KEY_A || keycode == ARROW_LEFT)
		game->actions.key_left = true;
	else if (keycode == KEY_D || keycode == ARROW_RIGHT)
    {
        game->actions.key_right = true;
        update(game);
    }
    else if (keycode == ESC)
        exit(0);
    return (0);
}

int on_key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == ARROW_UP)
		game->actions.key_up = false;
	else if (keycode == KEY_S || keycode == ARROW_DOWN)
		game->actions.key_down = false;
	else if (keycode == KEY_A || keycode == ARROW_LEFT)
		game->actions.key_left = false;
	else if (keycode == KEY_D || keycode == ARROW_RIGHT)
		game->actions.key_right = false;
    return (0);
}

void destroy_list(t_game *game, t_image *list)
{
    int i = 0;
    
    while (i < 3)
    {
        if (list[i].img_ptr) {
            mlx_destroy_image(game->mlx, list[i].img_ptr);
            list[i].img_ptr = NULL;
        }
        i++;
    }
}
void draw(t_game *game)
{

    int pos_x = game->player.pos.x;
	int pos_y = game->player.pos.y;
    char    sig;
    if (game->player.moving)
    {
        sig = game->map.coords[pos_y][pos_x + 1];
        if (sig != '1')
        {
            printf("por aqui puedes pasar\n");
            // Borra la ventana antes de dibujar la nueva imagen
            mlx_clear_window(game->mlx, game->window.win);

            int current_frame = game->player.current_frame - 1;
            if (current_frame >= 0)
            {
                // Dibuja la nueva imagen en la ventana limpia
                mlx_put_image_to_window(game->mlx, game->window.win, game->p[current_frame].img_ptr, game->player.pos.x * TILE_SIZE, game->player.pos.y * TILE_SIZE);
            }
        }
    }
    // draw_map(game);
}



int update(t_game *game)
{
    destroy_list(game, game->p);
    if (game->actions.key_right)
    {
        game->frame_count = 0;
        game->p[0] = new_file_img(game->mlx, "sprites/character1.xpm");
        game->p[1] = new_file_img(game->mlx, "sprites/character.xpm");
        game->p[2] = new_file_img(game->mlx, "sprites/character2.xpm");
        game->player.moving = 1;
        game->player.steps++;
        game->player.pos.x += 1;

        if (game->player.current_frame > 2)
            game->player.current_frame = 0;
        else
            game->player.current_frame++;
    }
    draw(game);
    return (0);
}