/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:05:25 by lcollado          #+#    #+#             */
/*   Updated: 2023/11/29 14:26:07 by lcollado         ###   ########.fr       */
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

# include "files.h"
# include "keys.h"

# define TILE_SIZE 64

int allowed_keys[] = {ARROW_RIGHT, ARROW_LEFT, ARROW_DOWN, ARROW_UP, KEY_A, KEY_D, KEY_S, KEY_W};
int allowed_keys_count = sizeof(allowed_keys) / sizeof(allowed_keys[0]);

/*COLORS*/
# define RED "\033[0m"

typedef struct s_vector {
	int	x;
	int	y;
}				t_vector;

# include "sprite.h"

typedef enum e_bool {
	false,
	true
}			t_bool;

typedef struct s_window {
	void		*win;
	t_vector	size;
}			t_window;

typedef struct s_map {
	t_vector	size;
	char		**coords;
	int			total_collec;
}				t_map;

typedef struct s_game {
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
int			valid_file(int argc, char *file);
int			valid_path(t_game *game);
int			valid_map(t_game *game);

// MAP
void		map_init(t_game *game, char *file);
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

#endif