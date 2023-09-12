#ifndef SPRITE_H
# define SPRITE_H

# include "game.h"

typedef struct s_image{
    void		*img_ptr;
	t_vector	size;
    char        *addr;
	int		    *pixels;
	int			bpp;
	int			line_size;
	int			endian;
}               t_image;

typedef struct s_sprite{
    t_list	* animations;
	char	* name;
	char	* file_path;
	t_image	    img;
    t_vector    dimensions;
    t_vector    pos;
    int         collec;
}               t_sprite;

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

typedef struct s_island {
    t_image top;
    t_image bottom;
    t_image left;
    t_image right;
    t_image k_curve;
    t_image w_curve;
    t_image a_curve;
    t_image j_curve;
    t_image boat;
    t_image star;
    t_image sand;
    t_image water;
}               t_island;

typedef struct s_field {
    t_image flower_blue;
    t_image flower_red;
    t_image flower_star;
    t_image rock;
    t_image ladder;
    t_image floor;
    t_image bush;
}               t_field;

typedef struct s_forest {
    t_image mushroom;
    t_image rock;
    t_image ladder;
    t_image floor;
    t_image tree;
}               t_forest;

typedef struct s_castle {
    t_image wall_top;
    t_image wall_bottom;
    t_image infill_wall;
    t_image hatch;
    t_image ladder;
    t_image floor;
    t_image torch;
    t_image candle;
}               t_castle;

typedef struct s_collection{
    t_image     bg;
    t_image     bg_down;
    t_image     bg_total_black;
    t_image     total_bg;
    t_image     start;
    t_image     game_over;
    t_image     restart;
    t_image     exit;
    t_image     won;
    t_image     arrow_up;
    t_image     arrow_down;
    t_image     arrow;
    t_image     press;
    t_image     logo;
    t_sprite    player_one;
    t_sprite    coin;
    t_sprite    enemy1;
    t_sprite    enemy2;
    t_font      score_font;
    t_island    island;
    t_field      field;
    t_forest    forest;
    t_castle    castle;
}               t_collection;

typedef	struct sprite_slice {
	int         x;
	int         y;
	int         width;
	int         height;
}	            sprite_slice;



/* Sprite */
t_sprite	new_sprite(char * name, char * file_path, void *mlx);
t_animation *	slice_sprite(t_sprite s, sprite_slice slice, int frames, int delay, enum entity e, void *mlx);
void	destroy_sprite(t_sprite s, void *mlx);



/* Images */
t_image	new_file_img(char * path, void *mlx);
t_image	new_img(int w, int h, void *mlx);


/* Image Utils*/
void	put_pixel_img(t_image img, int x, int y, int color);
unsigned int	get_pixel_img(t_image img, int x, int y);
void	destroy_image(t_image img, void *mlx);
void	put_img_to_img(t_image dst, t_image src, int x, int y);
void remove_img_from_img(t_image dst, t_image src, int x, int y);

#endif