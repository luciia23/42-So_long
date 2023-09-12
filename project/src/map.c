# include "game.h"

void    get_rowscols(t_map *map, char *file)
{
    char    *line;
    int     fd;

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        printf("error");
        return;
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

void read_map(t_map *map, char *file)
{
    char *line;
    int fd;
    int i;

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        printf("error");
        return;
    }
    map->coords = (char **)malloc(sizeof(char *) * (map->size.y + 1));
    if (!map->coords)
    {
        close(fd);
        return;
    }
    line = get_next_line(fd);
    i = 0;
    while (line)
    {
        map->coords[i] = strdup(line);
        free(line);
        line = get_next_line(fd);
        i++;
    }
    close(fd);
}



void    get_collec(t_map *map)
{
    int i;
    int j;

    i = 0;
    while (i < map->size.y)
    {
        j = 0;
        while (j < map->size.x)
        {
            if (map->coords[i][j] == 'C')
                map->total_collec++;
            j++;
        }
        i++;
    }
}

void    init_files(t_game *game)
{
    game->map.array[0] = MAP_1;
    game->map.array[1] = MAP_2;
    game->map.array[2] = MAP_3;
    game->map.array[3] = MAP_4;
}

void    map_init(t_game *game)
{
    int i = 0;
    init_files(game);
    game->current_map = 0;
    while (i < NUM_MAPS)
    {
        game->maps[i].size.x = 0;
        game->maps[i].size.y = 0;
        game->maps[i].coords = NULL;
        game->maps[i].total_collec = 0;
        get_rowscols(&game->maps[i], game->map.array[i]);
        read_map(&game->maps[i], game->map.array[i]);
        get_collec(&game->maps[i]);
        i++;
    }
    game->map = game->maps[game->current_map];
}

void	draw_map(t_game *game, t_image *moneda)
{
	int	i;
	int	j;

	i = 0;
    game->count_enemy = 0;
    destroy_image(game->collection.bg_down, game->mlx);
    game->collection.bg_down = new_file_img(BG_IMG, game->mlx);
    put_img_to_img(game->collection.bg_down, game->collection.logo, 9 * TILE_SIZE, 32);
    update_score(game);
	while (i < game->map.size.y)
	{
		j = 0;
		while (j < game->map.size.x)
		{
            draw_img(game, moneda, j, i);
			j++;
		}
		i++;
	}
   mlx_put_image_to_window(game->mlx, game->window.win, game->collection.bg_down.img_ptr, 0, game->map.size.y * TILE_SIZE);
}