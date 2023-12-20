/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:36:45 by lcollado          #+#    #+#             */
/*   Updated: 2023/12/20 12:59:09 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

int	ft_close(void)
{
	exit(0);
}

t_window	ft_new_window(void *mlx, int width, int height, char *title)
{
	t_window	window;

	window.win = mlx_new_window(mlx, width, height, title);
	mlx_hook(window.win, 17, 0, ft_close, 0);
	return (window);
}
