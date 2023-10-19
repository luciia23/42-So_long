/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:04:40 by lcollado          #+#    #+#             */
/*   Updated: 2023/10/19 15:05:04 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	ft_close(void)
{
	exit(0);
}

t_window	ft_new_window(void *mlx, int width, int height, char *title)
{
	t_window	window;

	// window = {0};
	window.win = mlx_new_window(mlx, width, height, title);
	mlx_hook(window.win, 17, 0, ft_close, 0);
	return (window);
}
