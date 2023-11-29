/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:26:05 by lcollado          #+#    #+#             */
/*   Updated: 2023/11/29 15:22:56 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

t_font	load_panel_font(t_game *game)
{
	game->collection.panel.zero = new_file_img(game->mlx, TEXT_NUMBER_0);
	game->collection.panel.one = new_file_img(game->mlx, TEXT_NUMBER_1);
	game->collection.panel.two = new_file_img(game->mlx, TEXT_NUMBER_2);
	game->collection.panel.three = new_file_img(game->mlx, TEXT_NUMBER_3);
	game->collection.panel.four = new_file_img(game->mlx, TEXT_NUMBER_4);
	game->collection.panel.five = new_file_img(game->mlx, TEXT_NUMBER_5);
	game->collection.panel.six = new_file_img(game->mlx, TEXT_NUMBER_6);
	game->collection.panel.seven = new_file_img(game->mlx, TEXT_NUMBER_7);
	game->collection.panel.eight = new_file_img(game->mlx, TEXT_NUMBER_8);
	game->collection.panel.nine = new_file_img(game->mlx, TEXT_NUMBER_9);
	return (game->collection.panel);
}

void	print_font(t_game *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->window.win, img, x, y);
}

void	put_font(t_game *game, int digit, int x, int y)
{
	if (digit == 0)
		print_font(game, game->collection.panel.zero.img_ptr, x, y);
	if (digit == 1)
		print_font(game, game->collection.panel.one.img_ptr, x, y);
	if (digit == 2)
		print_font(game, game->collection.panel.two.img_ptr, x, y);
	if (digit == 3)
		print_font(game, game->collection.panel.three.img_ptr, x, y);
	if (digit == 4)
		print_font(game, game->collection.panel.four.img_ptr, x, y);
	if (digit == 5)
		print_font(game, game->collection.panel.five.img_ptr, x, y);
	if (digit == 6)
		print_font(game, game->collection.panel.six.img_ptr, x, y);
	if (digit == 7)
		print_font(game, game->collection.panel.seven.img_ptr, x, y);
	if (digit == 8)
		print_font(game, game->collection.panel.eight.img_ptr, x, y);
	if (digit == 9)
		print_font(game, game->collection.panel.nine.img_ptr, x, y);
}

void	update_panel(t_game *game)
{
	int	x;
	int	y;
	int	i;
	int	steps;
	int	digit;

	i = 0;
	x = (game->map.size.x * TILE_SIZE) - TILE_SIZE;
	y = (game->map.size.y * TILE_SIZE);
	steps = game->player.steps;
	while (i < 4)
	{
		digit = steps % 10;
		steps /= 10;
		put_font(game, digit, x, y);
		i++;
		x -= TILE_SIZE;
	}
}
