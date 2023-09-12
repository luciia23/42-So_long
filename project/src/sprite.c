#include "game.h"

t_sprite	new_sprite(char * name, char * file_path, void *mlx) {
	t_image	img;

	img = new_file_img(file_path, mlx);
	return (t_sprite){NULL, strdup(name),
		ft_strdup(file_path), img, {img.size.x, img.size.y, 0},{0,0,0}, 0};
}

void	add_frame(t_animation * a, t_sprite s, sprite_slice slice, void *mlx) {
	t_image *	frame;
	int i, j;

	frame = (t_image *)calloc(sizeof(t_image), 1);
	if (!frame)
		return ;
	*frame = new_img(slice.width, slice.height, mlx);
	i = 0;
	while(i < slice.width) {
		j = 0;
		while(j < slice.height) {
//			put_pixel_img(*frame, slice.width - j, i, get_pixel_img(s.sprite_img, slice.x + j, slice.y + i));
			put_pixel_img(*frame, j, i, get_pixel_img(s.img, slice.x + j, slice.y + i));
			j++;
		}
		i++;
	}
	ft_lstadd_back(&a->frames, ft_lstnew(frame));
}

t_animation *	slice_sprite(t_sprite s, sprite_slice slice, int frames, int delay, enum entity e, void *mlx) {
	int i;
	t_animation *	a;

	a = (t_animation *)calloc(sizeof(t_animation), 1);
	if (!a)
		return NULL;
	*a = (t_animation){NULL, slice.width, slice.height, delay, 0, 0, 0, 0, e};
	i = 0;
	while (i < frames) {
		add_frame(a, s, slice, mlx);
		slice.x += slice.width;
		if (slice.x >= s.dimensions.x) {
			slice.x = 0;
			slice.y += slice.height;
		}
		i++;
	}
	return a;
}

void	destroy_sprite(t_sprite s, void *mlx) {
	free(s.name);
	free(s.file_path);
	destroy_image(s.img, mlx);
}