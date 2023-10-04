/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:03:59 by lcollado          #+#    #+#             */
/*   Updated: 2023/10/04 14:04:04 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void    game_init(t_game *game)
{
    game->mlx = mlx_init();
    game->window = ft_new_window(game->mlx, game->map.size.x * TILE_SIZE, (game->map.size.y * TILE_SIZE), "SO_LONG");
    img_init(game);
    draw_map(game);
}

int start(t_game *game, int argc, char *argv[])
{
    if (!valid_file(argc, argv[1]))
        return (0);
    map_init(game, argv[1]);
    if (!valid_map(&game->map))
    {
        free_map(&game->map);
        return (0);
    }
    game_init(game);
    return (1);
}

int main(int argc, char *argv[])
{
    t_game  game;

    if (!start(&game, argc, argv))
        return (0);
    mlx_hook(game.window.win, 2, 1L<<0, on_key_press, &game);
    mlx_hook(game.window.win, 3, 1L<<1, on_key_release, &game);
    mlx_loop(game.mlx);
    return (0);
}