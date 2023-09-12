#ifndef SPRITE_H
# define SPRITE_H

# include "game.h"

typedef struct s_image{
    void        *img_ptr;
    t_vector    size;
    char        *addr;
    int         *pixels;
    int         bpp;
    int         line_size;
    int         endian;
}               t_image;

typedef struct s_player{
    t_image     img;
    t_vector    pos;
    int         collec;
}               t_player;

typedef struct s_font{
    t_image     zero;
    t_image     one;
    t_image     two;
    t_image     three;
    t_image     four;
    t_image     five;
    t_image     six;
    t_image     seven;
    t_image     eight;
    t_image     nine;
}               t_font;

#endif