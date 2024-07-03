# include "so_long.h"

//check only '01CEP'
//check number of 'E' and 'P', 'C'
int  check_elements(t_map *map)
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
            {
                map->start = (t_point){x, y};
                map->player_n++;
            }
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

int check_shape(t_map *map)
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

int check_wall(t_map *map)
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

int find_path(t_map *map, t_point cur, char **matrix)
{
    static int collect = 0;
    static int find_exit = 0;

    if (matrix[cur.y][cur.x] == '1')
        return (0);
    else if (matrix[cur.y][cur.x] == 'C')
        collect++;
    else if (matrix[cur.y][cur.x] == 'E')
        find_exit = 1;
    matrix[cur.y][cur.x] = '1';
    find_path(map, (t_point){cur.x + 1, cur.y}, matrix);
    find_path(map, (t_point){cur.x - 1, cur.y}, matrix);
    find_path(map, (t_point){cur.x, cur.y + 1}, matrix);
    find_path(map, (t_point){cur.x, cur.y - 1}, matrix);
    if (collect == map->collect_all && find_exit == 1)
        return (1);
    return (0);
}

//copy a map grid, find path, find 0 and collect and exit, start
int check_path(t_map *map)
{
    char **matrix;
    int i;
    int path;

    i = 0;
    path = 0;
    matrix = malloc((map->rows + 1) * (sizeof(char *)));
    if (!matrix)
        error_info(map, "Malloc error when check valid path.");
    while (i < map->rows)
    {
        matrix[i] = ft_strdup(map->grid[i]);
        if (!matrix[i])
        {
            delete_matrix(matrix, i);
            error_info(map, "Malloc error when check valid path.");
        }
        i++;
    }
    path = find_path(map, map->start, matrix);
    delete_matrix(matrix, i);
    return (path);
}
