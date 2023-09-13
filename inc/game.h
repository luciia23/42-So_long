#ifndef GAME_H
# define GAME_H

#include "../mlx/mlx.h"
#include "../libft/libft.h"

# include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "files.h"


#define TILE_SIZE 64

typedef struct s_vector {
    int x;
    int y;
}               t_vector;

#include "sprite.h"

typedef enum e_bool {
    false,
    true
}           t_bool;

typedef struct s_window {
    void        *win;
    t_vector    size;
}             t_window;

typedef struct s_map {
    t_vector    size;
    char        **coords;
    int         total_collec;
}               t_map;

typedef struct s_game {
    void            *mlx;
    t_window        window;
    t_map           map;
    t_collection    collection;
    int             movements;
}               t_game;

// WINDOW
t_window    ft_new_window(void *mlx, int width, int height, char *title);

// CHECK
int valid_file(int argc, char *file);
int valid_map(t_map *map);

// MAP
void map_init(t_game *game, char *file);
void    draw_map(t_game *game);

// UTILS
int    error(char *msg);

// IMG
void    img_init(t_game *game);
void    draw_img(t_game *game, int x, int y);


#endif