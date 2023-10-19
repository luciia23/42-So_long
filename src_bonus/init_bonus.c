/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:20:34 by lcollado          #+#    #+#             */
/*   Updated: 2023/10/19 13:27:49 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

void    init_player(t_game *game)
{
    int i;
    int j;
    i = 0;
    while (i < game->map.size.y)
    {
        j = 0;
        while (game->map.coords[i][j])
        {
            if (game->map.coords[i][j] == 'P')
            {
                game->player.pos.x = j;
                game->player.pos.y = i;
            }
            j++;
        }
        i++;
    }
    game->player.collec = 0;
    game->player.steps = 0;
    game->player.current_frame = -1;
}

void    add_enemy(t_game *game, int x, int y)
{
    t_enemy *new_enemy;

    new_enemy = malloc(sizeof(t_enemy));
    new_enemy->sprite = new_sprite(game->mlx, LINK_IMG);
    new_enemy->sprite.pos.x = 0;
    new_enemy->sprite.pos.y = 0;
    new_enemy->sprite.pos.x += x;
    new_enemy->sprite.pos.y += y;
    new_enemy->next = game->enemies;
    game->enemies = new_enemy;
}

void    init_enemies(t_game *game)
{
    // int enemy_count;
    int i;
    int j;

    // enemy_count = 0;
    i = 0;
    game->enemy_count = 0;
    while(i < game->map.size.y)
    {
        j = 0;
        while(j < game->map.size.x)
        {
            if(game->map.coords[i][j] == 'D')
            {
                // game->enemies[enemy_count].sprite.pos.x = j;
                // game->enemies[enemy_count].sprite.pos.y = i;
                // enemy_count++;
                game->enemy_count++;
                add_enemy(game, j, i);
            }
            j++;
        }
        i++;
    }
}