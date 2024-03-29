/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:05:25 by lcollado          #+#    #+#             */
/*   Updated: 2024/02/11 17:37:26 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"

# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdint.h>

# include "utils.h"
# include "files.h"
# include "keys.h"
# include "sprite.h"

# define TILE_SIZE 64

/*COLORS*/
# define RED "\033[0m"

typedef struct s_window
{
	void		*win;
	t_vector	size;
}			t_window;

typedef struct s_map
{
	t_vector	size;
	char		**coords;
	int			total_collec;
	int			e_flag;
}				t_map;

typedef struct s_game
{
	void			*mlx;
	t_window		window;
	t_map			map;
	t_collection	collection;
	int				movements;
	int				moving;
	int				collec;
}					t_game;

// WINDOW
t_window	ft_new_window(void *mlx, int width, int height, char *title);

// CHECK
int			valid_file(int argc, char *file, char *end);
int			valid_path(t_game *game);
int			valid_map(t_game *game);

// MAP
int			map_init(t_game *game, char *file);
void		draw_map(t_game *game);
t_map		copy_map(const t_map *original);

// UTILS
int			error(char *msg);
void		init_player(t_game *game);
int			ft_strlen_nonl(char *str);

// IMG
void		img_init(t_game *game);
void		draw_img(t_game *game, int x, int y);
t_image		new_file_img(void *mlx, char *path);
t_sprite	new_sprite(void *mlx, char *file_path);

//FREE
void		free_map(t_map *map);

//HOOKS
int			on_key_press(int keycode, t_game *game);
int			on_key_release(int keycode, t_game *game);
void		print_steps(t_game *game);
int			is_valid_move(t_game *game, int x, int y);
void		move_player(t_game *game, int x, int y);
int			movement_verification(t_game *game, int new_x, int new_y);
void		verify_collec(int x, int y, t_game *game);

#endif