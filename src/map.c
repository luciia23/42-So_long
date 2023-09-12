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

void    map_init(t_game *game, char *file)
{
    game->map.size.x = 0;
    game->map.size.y = 0;
    game->map.coords = NULL;
    game->map.total_collec = 0;
    get_rowcols(&game->map, file);
    read_map(&game->map, file);
    get_collec(&game->map);
}