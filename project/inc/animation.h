#ifndef ANIMATION_H
# define ANIMATION_H

# include "../mlx/mlx.h"
# include "game.h"

enum entity {
	PLAYER,
	ENEMY,
	EVENT,
	OBJ,
};

typedef struct s_animation {
	t_list *	frames;
	int		width;
	int		height;
	int		delay;			// How many fps it takes to change animation
	int		_tmp_delay;		// Delay Iterator
	int		current_frame_num;	// Which frame is selected
	long int	last_updated;		// When was the last update
	long int	frame_count;		// The frame count
	enum entity	entity;
}		t_animation;


#endif