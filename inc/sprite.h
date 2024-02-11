/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:05:51 by lcollado          #+#    #+#             */
/*   Updated: 2024/02/10 12:08:51 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include "game.h"

typedef struct s_image
{
	void		*img_ptr;
	t_vector	size;
	char		*addr;
	int			*pixels;
	int			bpp;
	int			line_size;
	int			endian;
}				t_image;

typedef struct s_sprite
{
	t_image		img;
	t_vector	pos;
}				t_sprite;

typedef struct s_font
{
	t_image		zero;
	t_image		one;
	t_image		two;
	t_image		three;
	t_image		four;
	t_image		five;
	t_image		six;
	t_image		seven;
	t_image		eight;
	t_image		nine;
}				t_font;

typedef struct s_collection
{
	t_sprite	player;
	t_image		floor;
	t_image		wall;
	t_image		coin;
	t_image		exit;
	t_image		open_exit;
}				t_collection;

#endif