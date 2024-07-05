#include "so_long_bonus.h"

void enemy_gridnext(t_map *map)
{
    t_point cur;
    t_point next;

    cur = map->enemy_sp;
    if (map->enemy_d == 'r')
        next = (t_point){cur.x + 1, cur.y};
    else if (map->enemy_d == 'l')
        next = (t_point){cur.x - 1, cur.y};
    if (map->grid[next.y][next.x] == '1' || map->grid[next.y][next.x] == 'C')
    {
        if (map->enemy_d == 'r')
            map->enemy_d = 'l';
        else if (map->enemy_d == 'l')
            map->enemy_d = 'r';
    }
    else
    {
        map->image.enemy->instances[0].x = next.x * map->scale;
	    map->image.enemy->instances[0].y = next.y * map->scale;
        map->grid[cur.y][cur.x] = '0';
        map->grid[next.y][next.x] = 'H';
        map->enemy_sp = next;
    }
}

void enemy_move(t_map *map, double time)
{
    static double now = 0;

    now += time;
    if (now > 1)
    {
        enemy_gridnext(map);
        now -= 1;
    }
}