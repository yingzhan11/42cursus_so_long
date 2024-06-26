# include "so_long.h"

void my_keyhook(mlx_key_data_t keydata, void *param)
{
    t_map *map;

    map = (t_map *)param;
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        quit_game(map);
    if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
    {
        map->next = (t_coord){map->cur.x, map->cur.y - 1};
        player_move(map, map->image);
    }
    if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
    {
        map->next = (t_coord){map->cur.x, map->cur.y + 1};
        player_move(map, map->image);
    }
    if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
    {
        map->next = (t_coord){map->cur.x - 1, map->cur.y};
        player_move(map, map->image);
    }
    if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
    {
        map->next = (t_coord){map->cur.x + 1, map->cur.y};
        player_move(map, map->image);
    }
}

void    my_closehook(void *param)
{
    t_map *map;
    
    map = (t_map *)param;
    delete_map(map);
    exit(EXIT_SUCCESS);
}