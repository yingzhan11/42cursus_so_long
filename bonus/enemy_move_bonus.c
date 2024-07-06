#include "so_long_bonus.h"

void enemy_gridnext(t_map *map, int i)
{
    t_point cur;
    t_point next;

    cur = map->enemy[i].pos;
    if (map->enemy[i].dir == 'r')
        next = (t_point){cur.x + 1, cur.y};
    else if (map->enemy[i].dir == 'l')
        next = (t_point){cur.x - 1, cur.y};
    if (map->grid[next.y][next.x] == '1' || map->grid[next.y][next.x] == 'C')
    {
        if (map->enemy[i].dir == 'r')
            map->enemy[i].dir = 'l';
        else if (map->enemy[i].dir == 'l')
            map->enemy[i].dir = 'r';
    }
    else
    {
        map->image.enemy->instances[i].x = next.x * map->scale;
	    map->image.enemy->instances[i].y = next.y * map->scale;
        map->grid[cur.y][cur.x] = '0';
        map->grid[next.y][next.x] = 'H';
        map->enemy[i].pos = next;
    }
    if (map->enemy[i].pos.x == map->cur.x && map->enemy[i].pos.y == map->cur.y)
    {
        ft_printf("GAME OVER!\n");
		quit_game(map);
    }
}

void enemy_all(t_map *map)
{
    int i;

    i = 0;
    while (i < map->enemy_n)
    {
        enemy_gridnext(map, i);
        i++;
    }
}

void enemy_move(t_map *map, double time)
{
    static double now = 0;

    now += time;
    if (now > 1)
    {
        enemy_all(map);       
        now -= 1;
    }
}