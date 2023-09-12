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

typedef struct s_vector {
    int x;
    int y;
}               t_vector;

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
    void        *mlx;
    t_window    window;
    t_map       map;
    int         collec;
}               t_game;

void    error(char *msg);

#endif