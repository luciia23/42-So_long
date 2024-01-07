/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollado <lcollado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:42:25 by lcollado          #+#    #+#             */
/*   Updated: 2023/12/28 12:16:38 by lcollado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

void	get_rowscols(t_map *map, char *file)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("wrong fd");
		return ;
	}
	line = get_next_line(fd);
	map->size.x = ft_strlen(line) - 1;
	while (line)
	{
		map->size.y++;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
}

void	read_map(t_map *map, char *file)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("wrong fd");
		return ;
	}
	map->coords = (char **)malloc(sizeof(char *) * (map->size.y + 1));
	if (!map->coords)
	{
		close(fd);
		return ;
	}
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		map->coords[i++] = strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	map_init(t_game *game, char *file)
{
	game->map.size.x = 0;
	game->map.size.y = 0;
	game->map.coords = NULL;
	game->map.total_collec = 0;
	get_rowscols(&game->map, file);
	read_map(&game->map, file);
	init_player(game);
}

void	draw_map(t_game *game, int flag)
{
	int	i;
	int	j;

	i = 0;
	update_panel(game);
	while (i < game->map.size.y)
	{
		j = 0;
		while (j < game->map.size.x)
		{
			draw_img(game, j, i, flag);
			j++;
		}
		i++;
	}
}

t_map	copy_map(const t_map *original)
{
	t_map	copy;
	int		i;
	int		j;

	copy.size = original->size;
	copy.total_collec = original->total_collec;
	copy.coords = (char **)malloc(original->size.y * sizeof(char *));
	i = 0;
	while (i < original->size.y)
	{
		copy.coords[i] = (char *)malloc(original->size.x * sizeof(char));
		j = 0;
		while (j < original->size.x)
		{
			copy.coords[i][j] = original->coords[i][j];
			j++;
		}
		i++;
	}
	return (copy);
}
