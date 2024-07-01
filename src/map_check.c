# include "so_long.h"

//check only '01CEP'
//check number of 'E' and 'P', 'C'
static int  check_elements(t_map *map)
{
    int y;
    int x;

    y = -1;
    while (++y < map->rows)
    {
        x = -1;
        while (++x < map->cols)
        {
            if (!ft_strchr(ELEMENTS, map->grid[y][x]))
                return (0);
            else if (map->grid[y][x] == 'P')
                map->player_n++;
            else if (map->grid[y][x] == 'E')
                map->exit_n++;
            else if (map->grid[y][x] == 'C')
                map->collect_all++;
        }
    }
    if (map->player_n == 1 && map->exit_n == 1 && map->collect_all >= 1)
        return (1);
    return (0);
}

static int check_shape(t_map *map)
{
    size_t len;
    int y;

    y = 0;
    len = ft_strlen(map->grid[y]);
    while (y < map->rows)
    {
        if (ft_strlen(map->grid[y]) != len)
            return (0);
        y++;
    }
    map->cols = len;
    return (1);
}

static int check_wall(t_map *map)
{
    int i;

    i = 0;
    while (i < map->cols)
    {
        if (map->grid[0][i] != '1' || map->grid[map->rows - 1][i] != '1')
            return (0);
        i++;
    }
    i = 0;
    while (i < map->rows)
    {
        if (map->grid[i][0] != '1' || map->grid[i][map->cols - 1] != '1')
            return (0);
        i++;
    }
    return (1);

}

void    check_map(t_map *map)
{
    if (map->rows == 0)
        error_info(map, "Map is empty.");
    //check shape, rectangular
    if (check_shape(map) == 0)
        error_info(map, "Map is not a rectangular.");
    //check elements '01CEP' only 1E, 1C, 1P
    if (check_elements(map) == 0)
        error_info(map, "Elements of map is invalid.");
    //check closed walls
    if (check_wall(map) == 0)
        error_info(map, "The map is not closed by walls.");
    //check path, atleast a valid path
}



