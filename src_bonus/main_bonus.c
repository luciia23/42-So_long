/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 20:00:05 by lcollado          #+#    #+#             */
/*   Updated: 2024/01/09 22:11:23 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

void	init(t_game *game)
{
	game->mlx = mlx_init();
	game->window = ft_new_window(game->mlx, game->map.size.x * TILE_SIZE,
			(game->map.size.y * TILE_SIZE) + 64, "SO_LONG");
	init_img(game);
	game->actions = (t_actions){false, false, false, false};
	init_enemies(game);
	draw_map(game, 1);
}

int	start(t_game *game, int argc, char *argv[])
{
	if (!valid_file(argc, argv[1], ".ber"))
		return (0);
	if (map_init(game, argv[1]))
	{
		if (!valid_map(game))
		{
			free_map(&game->map);
			return (0);
		}
		init(game);
	}
	return (1);
}

void	check_leaks(void)
{
	system("leaks so_log_bonus");
}

int	main(int argc, char **argv)
{
	t_game	game;

	atexit(check_leaks);
	if (!start(&game, argc, argv))
		return (0);
	mlx_hook(game.window.win, 2, 1L << 0, on_key_press, &game);
	mlx_hook(game.window.win, 3, 1L << 1, on_key_release, &game);
	mlx_loop(game.mlx);
	return (0);
}
