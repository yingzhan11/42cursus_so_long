# include "so_long.h"

void    delete_image(t_map *map)
{
    if (map->image->empty)
        mlx_delete_image(map->mlx, map->image->empty);
    if (map->image->wall)
        mlx_delete_image(map->mlx, map->image->wall);
    if (map->image->collect)
        mlx_delete_image(map->mlx, map->image->collect);
    if (map->image->exit1)
        mlx_delete_image(map->mlx, map->image->exit1);
    if (map->image->exit2)
        mlx_delete_image(map->mlx, map->image->exit2);
    if (map->image->start)
        mlx_delete_image(map->mlx, map->image->start);
    if (map->image->player)
        mlx_delete_image(map->mlx, map->image->player);
}

void    delete_map(t_map *map)
{
    int y;

    y = 0;
    if (!map)
        return ;
    if (map->image)
        delete_image(map);
    if (map->grid)
    {
        while (y < map->rows)
        {
            free (map->grid[y]);
            y++;
        }
        free (map->grid);
    }
    if (map->mlx)
        mlx_terminate(map->mlx);
}

void    quit_game(t_map *map)
{
    delete_map(map);
    exit(EXIT_SUCCESS);
}

void    error_info(t_map *map, char *message)
{
    delete_map(map);
    ft_printf("Error: %s\n", message);
    exit(EXIT_FAILURE);
}