/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 20:37:25 by lcollado          #+#    #+#             */
/*   Updated: 2023/12/11 14:48:45 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_BONUS_H
# define GAME_BONUS_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"

# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdint.h>

# include "files.h"
# include "keys.h"

# define TILE_SIZE 64

/*COLORS*/
# define RED "\033[0m"

typedef struct s_vector {
	int	x;
	int	y;
}				t_vector;

# include "sprite_bonus.h"

typedef enum e_bool {
	false,
	true
}			t_bool;

typedef struct s_window {
	void		*win;
	t_vector	size;
}				t_window;

typedef struct s_map {
	t_vector	size;
	char		**coords;
	int			total_collec;
}				t_map;

typedef struct s_player {
	t_vector	pos;
	t_image		*front;
	t_image		*back;
	t_image		*left;
	t_image		*right;
	int			steps;
	int			collec;
	int			current_frame;
}				t_player;

typedef struct s_enemy
{
	t_sprite	sprite;
	struct		s_enemy	*next;
}				t_enemy;

typedef struct s_actions {
	t_bool	key_up;
	t_bool	key_down;
	t_bool	key_left;
	t_bool	key_right;
}			t_actions;

typedef struct s_game
{
	void			*mlx;
	t_window		window;
	t_map			map;
	t_collection	collection;
	t_player		player;
	t_enemy			*enemies;
	t_actions		actions;
	int				enemy_count;
}					t_game;

// CHECK
int			valid_file(int argc, char *file);
int			valid_map(t_game *game);
int	valid_path(t_game *game);

// UTILS
int			error(char *msg);
void		free_map(t_map *map);
void		win_game(t_game *game);
void		lose_game(t_game *game);
void    free_enemy(t_enemy *enemy);
int	ft_strlen_nonl(char *str);

// WINDOW
t_window	ft_new_window(void *mlx, int width, int height, char *title);

// MAP
void		map_init(t_game *game, char *file);
t_map		copy_map(const t_map *original);
void    draw_map(t_game *game, int flag);


// IMAGES
t_sprite	new_sprite(void *mlx, char *file_path);
t_image		new_file_img(void *mlx, char *path);
void    draw_img(t_game *game, int x, int y, int flag);

// PANEL
t_font		load_panel_font(t_game *game);
void		update_panel(t_game *game);

// INIT
void		init_enemies(t_game *game);
void		init_img(t_game *game);
void		init_player(t_game *game);

// HOOKS
int			on_key_press(int keycode, t_game *game);
int			on_key_release(int keycode, t_game *game);
int			update(t_game *game);
#endif
