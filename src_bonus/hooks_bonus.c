/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:07:48 by lcollado          #+#    #+#             */
/*   Updated: 2023/11/29 14:19:44 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

int on_key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == ARROW_UP)
	{
		game->actions.key_up = true;
		update(game);
	}
	else if (keycode == KEY_S || keycode == ARROW_DOWN)
	{
		game->actions.key_down = true;
		update(game);
	}
	else if (keycode == KEY_A || keycode == ARROW_LEFT)
	{
		game->actions.key_left = true;
		update(game);
	}
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

void	check_frames(t_game *game)
{
	if (game->player.current_frame >= 2)
		game->player.current_frame = 0;
	else
		game->player.current_frame++;
}

int	movement(t_game *game, int x, int y)
{
	int	x_pos;
	int	y_pos;
	char sig;

	x_pos = game->player.pos.x + x;
	y_pos = game->player.pos.y + y;

	sig = game->map.coords[y_pos][x_pos];
	if (sig != '1' && (sig != 'E' || ( sig == 'E' && game->player.collec == game->map.total_collec)))
		return (1);
	else
		return (0);
}

int	enemy_movement(t_game *game, int x, int y, t_enemy *enemy)
{
	int	x_pos;
	int	y_pos;
	char	sig;

	x_pos = enemy->sprite.pos.x + x;
	y_pos = enemy->sprite.pos.y + y;
	sig = game->map.coords[y_pos][x_pos];
	if (sig == '0')
	{
		enemy->sprite.pos.x = x_pos;
		enemy->sprite.pos.y = y_pos;
		return (1); 
	}
	else
		return (0);
}
void	verify(int x, int y, t_game *game)
{
	if (game->map.coords[y][x] == 'C')
	{
		game->map.coords[y][x] = '0';
		game->player.collec++;
		
		if (game->player.collec == game->map.total_collec)
		{
			if (game->collection.exit.img_ptr)
        		mlx_destroy_image(game->mlx, game->collection.exit.img_ptr);
			game->collection.exit.img_ptr = mlx_xpm_file_to_image(game->mlx, OPEN_EXIT_IMG, (int *)&game->collection.exit.size.x, (int *)&game->collection.exit.size.y);
		}
	}
	else if (game->map.coords[y][x] == 'D')
		lose_game(game);
	else if ((game->map.coords[y][x] == 'E' && game->player.collec == game->map.total_collec))
		win_game(game);
}

void move_player(t_game *game, int dx, int dy, t_image *image) {
    game->player.pos.x += dx;
    game->player.pos.y += dy;
	game->player.steps++;
	verify(game->player.pos.x, game->player.pos.y, game);
    mlx_clear_window(game->mlx, game->window.win);
    draw_map(game, 0);
    mlx_put_image_to_window(game->mlx, game->window.win, image[game->player.current_frame].img_ptr, game->player.pos.x * TILE_SIZE, game->player.pos.y * TILE_SIZE);
}

void	draw_enemy(t_game *game, int x, int y, t_enemy *enemy)
{
	int	e_x = enemy->sprite.pos.x + x;
	int	e_y = enemy->sprite.pos.y + y;
	game->map.coords[enemy->sprite.pos.y][enemy->sprite.pos.x] = '0';
	game->map.coords[e_y][e_x] = 'D';
}

void move_enemy(t_game *game, t_enemy *enemy) {
    int r = rand() % 4;

    int dx = 0;
    int dy = 0;

    if (r == 0) {
        dx = 1;
    } else if (r == 1) {
        dy = -1;
    } else if (r == 2) {
        dx = -1;
    } else if (r == 3) {
        dy = 1;
    }

    int new_x = enemy->sprite.pos.x + dx;
    int new_y = enemy->sprite.pos.y + dy;

    if (enemy_movement(game, dx, dy, enemy)) {
        game->map.coords[enemy->sprite.pos.y - dy][enemy->sprite.pos.x - dx] = '0';

        enemy->sprite.pos.x = new_x;
        enemy->sprite.pos.y = new_y;

        game->map.coords[enemy->sprite.pos.y][enemy->sprite.pos.x] = 'D';
		draw_map(game, 0);
    }
}


void move_enemies(t_game *game, t_enemy *enemies) {
    t_enemy *current;
	int	i;
	
	current = enemies;
	i = 0;
    while (current && i < game->enemy_count)
	{
        move_enemy(game, current);
		i++;
        current = current->next;
    }
}

void	draw_player(t_game *game, t_image *image)
{
	mlx_clear_window(game->mlx, game->window.win);
    draw_map(game, 0);
    mlx_put_image_to_window(game->mlx, game->window.win, image[game->player.current_frame].img_ptr, game->player.pos.x * TILE_SIZE, game->player.pos.y * TILE_SIZE);
}

void    check_collision(t_game *game)
{
    t_enemy *current = game->enemies;
    while (current) {
        if (game->player.pos.x == current->sprite.pos.x && game->player.pos.y == current->sprite.pos.y) {
            // El jugador ha chocado con un enemigo, realiza la acción correspondiente (por ejemplo, perder el juego).
            lose_game(game);
            return ; // No muevas al jugador si ha chocado con un enemigo.
        }
        current = current->next;
    }
}

int update(t_game *game)
{
	move_enemies(game, game->enemies);
	check_frames(game);
	// check_collision(game);
	if (game->actions.key_right)
	{
		if (movement(game, 1, 0))
			move_player(game, 1, 0, game->player.right);
		else
			draw_player(game, game->player.right);	
	}
	else if (game->actions.key_left)
	{
		if (movement(game, -1, 0))
			move_player(game, -1, 0, game->player.left);
		else
			draw_player(game, game->player.left);	
	}
	else if (game->actions.key_up)
	{
		if (movement(game, 0, -1))
			move_player(game, 0, -1, game->player.back);
		else
			draw_player(game, game->player.back);
	}
	else if (game->actions.key_down)
	{
		if (movement(game, 0, 1))
			move_player(game, 0, 1, game->player.front);
		else
			draw_player(game, game->player.front);
	}
	return (0);
}