# include "game.h"

void    get_rowscols(t_map *map, char *file)
{
    char    *line;
    int     fd;

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        printf("wrong fd");
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
        printf("wrong fd");
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

void    map_init(t_game *game, char *file)
{       
    game->map.size.x = 0;
    game->map.size.y = 0;
    game->map.coords = NULL;
    game->map.total_collec = 0;
    get_rowscols(&game->map, file);
    read_map(&game->map, file);
}

void    draw_map(t_game *game)
{
    int i;
    int j;

    i = 0;
    while(i < game->map.size.y)
    {
        j = 0;
        while (j < game->map.size.x)
        {
            draw_img(game, j, i);
            j++;
        }
        i++;
    }
}