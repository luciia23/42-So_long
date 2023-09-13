#include "game.h"

int valid_file(int argc, char *file)
{
    int len;
    if (argc == 1)
        return (error("there are no args"));
    len = ft_strlen(file);
    if(!ft_strnstr(file, ".ber", len))
        return (error("file extension should be .ber"));
    return (1);
}

int check_rectangular(t_map *map)
{
    int initial_len;
    int i;
    int actual_len;

    initial_len = ft_strlen(map->coords[0]);
    i = 1;
    while (i < map->size.y)
    {
        actual_len = ft_strlen(map->coords[i]);

        if (actual_len != initial_len)
            return (error("the map isn't rectangular"));
        i++;
    }
    return (1);
}

int valid_border(int x, int y, t_map *map)
{
    if ((y == 0 || x == 0 || y == map->size.y - 1 || x == map->size.x - 1) 
        && map->coords[y][x] != '1')
        return (0);
    return (1);

}

int valid_char(char c)
{
    if (c == '1' || c == '0' || c == 'C' || c == 'E' || c == 'P' )
        return (1);
    return (0);
}

// if(!ft_strchr("01CEP, map->coords[y][x]"))

int check_border(t_map *map)
{
    int y;
    int x;

    y = 0;
    while (y < map->size.y)
    {
        x = 0;
        while (x < map->size.x)
        {
            if (!valid_border(x, y, map))
                return (error("the border map isn't closed"));
            if (valid_char(map->coords[y][x]))
                return (error("there are wrong characters"));
            x ++;
        }
        y++;
    }
    return (1);
}

int check_chars(t_map *map)
{
    int i;
    int j;
    int p;
    int e;

    i = 0;
    p = 0;
    e = 0;
    while (i < map->size.y)
    {
        j = 0;
        while (j < map->size.x)
        {
            if (map->coords[i][j] == 'P')
                p++;
            if (map->coords[i][j] == 'E')
                e++;
            if (map->coords[i][j] == 'C')
                map->total_collec++;
            j++;
        }
        i++;
    }
    if (p != 1 || e != 1 || map->total_collec == 0)
        return(error("map has to have 1 P, 1 E and at least 1 C"));
    return (1);
}

int valid_map(t_map *map)
{
    check_rectangular(map);
    check_border(map);
    check_chars(map);
}