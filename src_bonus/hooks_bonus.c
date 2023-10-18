/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:07:48 by lcollado          #+#    #+#             */
/*   Updated: 2023/10/18 14:44:09 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

int on_key_press(int keycode, t_game *game)
{
	// printf("%d\n", keycode);
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

void	img(t_game *game, int x, int y)
{
	if (game->map.coords[y][x] == '1' || game->map.coords[y][x] == 'E' || game->map.coords[y][x] == 'C' || game->map.coords[y][x] == 'P' || game->map.coords[y][x] == 'D')
        mlx_put_image_to_window(game->mlx, game->window.win, game->collection.floor.img_ptr, x *  TILE_SIZE, y * TILE_SIZE); 
    if (game->map.coords[y][x] == '1')
        mlx_put_image_to_window(game->mlx, game->window.win, game->collection.wall.img_ptr,x * TILE_SIZE, y* TILE_SIZE);
    else if (game->map.coords[y][x] == 'C')
        mlx_put_image_to_window(game->mlx, game->window.win,game->collection.coin.img_ptr, x * TILE_SIZE, y * TILE_SIZE);
    else if (game->map.coords[y][x] == 'E')
        mlx_put_image_to_window(game->mlx,game->window.win, game->collection.exit.img_ptr, x * TILE_SIZE, y * TILE_SIZE);
    else if (game->map.coords[y][x] == '0')
        mlx_put_image_to_window(game->mlx, game->window.win, game->collection.floor.img_ptr, x * TILE_SIZE, y * TILE_SIZE);
}

void	draw(t_game *game)
{
	int i;
    int j;

    i = 0;
    update_panel(game);
    while(i < game->map.size.y)
    {
        j = 0;
        while (j < game->map.size.x)
        {
            img(game, j, i);
            j++;
        }
        i++;
    }
}

void	verify_collec(int x, int y, t_game *game)
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
	else if ((game->map.coords[y][x] == 'E' && game->player.collec == game->map.total_collec))
	{
        printf("THE END");
        mlx_destroy_window(game->mlx, game->window.win);
        exit(0);
	}
}

void	make_d(t_game *game)
{	
	game->player.pos.x += 1;
	mlx_clear_window(game->mlx, game->window.win);
	draw(game);
	mlx_put_image_to_window(game->mlx, game->window.win, game->collection.floor.img_ptr, game->player.pos.x * TILE_SIZE, game->player.pos.y * TILE_SIZE);
	mlx_put_image_to_window(game->mlx, game->window.win, game->player.right[game->player.current_frame].img_ptr, game->player.pos.x * TILE_SIZE, game->player.pos.y * TILE_SIZE);
	verify_collec(game->player.pos.x, game->player.pos.y, game);
}

void	make_a(t_game *game)
{	
	game->player.pos.x -= 1;
	mlx_clear_window(game->mlx, game->window.win);
	draw(game);
	mlx_put_image_to_window(game->mlx, game->window.win, game->collection.floor.img_ptr, game->player.pos.x * TILE_SIZE, game->player.pos.y * TILE_SIZE);
	mlx_put_image_to_window(game->mlx, game->window.win, game->player.left[game->player.current_frame].img_ptr, game->player.pos.x * TILE_SIZE, game->player.pos.y * TILE_SIZE);
	verify_collec(game->player.pos.x, game->player.pos.y, game);
}

void	make_s(t_game *game)
{	
	game->player.pos.y += 1;
	mlx_clear_window(game->mlx, game->window.win);
	draw(game);
	mlx_put_image_to_window(game->mlx, game->window.win, game->collection.floor.img_ptr, game->player.pos.x * TILE_SIZE, game->player.pos.y * TILE_SIZE);
	mlx_put_image_to_window(game->mlx, game->window.win, game->player.front[game->player.current_frame].img_ptr, game->player.pos.x * TILE_SIZE, game->player.pos.y * TILE_SIZE);
	verify_collec(game->player.pos.x, game->player.pos.y, game);
}

void	make_w(t_game *game)
{	
	game->player.pos.y -= 1;
	mlx_clear_window(game->mlx, game->window.win);
	draw(game);
	mlx_put_image_to_window(game->mlx, game->window.win, game->collection.floor.img_ptr, game->player.pos.x * TILE_SIZE, game->player.pos.y * TILE_SIZE);
	mlx_put_image_to_window(game->mlx, game->window.win, game->player.back[game->player.current_frame].img_ptr, game->player.pos.x * TILE_SIZE, game->player.pos.y * TILE_SIZE);
	verify_collec(game->player.pos.x, game->player.pos.y, game);
}

// void	enemy_moves(t_game *game)
// {
// 	int r = rand() % 3;
	
// 	if (r == 0)
// 	{
// 		game->enemies->sprite.pos.x += 1;
// 	}
	
// }

int update(t_game *game)
{
	game->player.moving = 1;
	check_frames(game);
	// enemy_moves(game);
	if (game->actions.key_right)
	{
		if (movement(game, 1, 0))
		{
			game->player.steps++;
			make_d(game);	
		}
	}
	else if (game->actions.key_left)
	{
		if (movement(game, -1, 0))
		{
			game->player.steps++;
			make_a(game);	
		}
	}
	else if (game->actions.key_up)
	{
		if (movement(game, 0, -1))
		{
			game->player.steps++;
			make_w(game);	
		}
	}
	else if (game->actions.key_down)
	{
		if (movement(game, 0, 1))
		{
			game->player.steps++;
			make_s(game);	
		}
	}
	return (0);
}