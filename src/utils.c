/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:02:39 by lcollado          #+#    #+#             */
/*   Updated: 2024/01/10 13:05:03 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	error(char *msg)
{
	ft_putstr_fd("\033[0;31m" " Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

void	print_steps(t_game	*game)
{
	ft_putstr_fd("Steps: ", 1);
	ft_putnbr_fd(game->movements, 1);
	ft_putchar_fd('\n', 1);
}

int	ft_strlen_nonl(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}
