#include "so_long_bonus.h"

void enemy_right_left(t_map *map, int i)
{
    t_point cur;
    t_point next;

    cur = map->enemy[i].pos;
    if (map->enemy[i].dir == 'r')
        next = (t_point){cur.x + 1, cur.y};
    else if (map->enemy[i].dir == 'l')
        next = (t_point){cur.x - 1, cur.y};
    if (map->grid[next.y][next.x] == '1' || map->grid[next.y][next.x] == 'C' || map->grid[next.y][next.x] == 'V')
    {
        if (map->enemy[i].dir == 'r')
        {
            map->enemy[i].dir = 'l';
			map->enemy[i].rows = 1;
            copy_anima_to_image(map->enemy[i].image, map->image.enemy_a, 0, 1);
        }
        else if (map->enemy[i].dir == 'l')
        {
            map->enemy[i].dir = 'r';
			map->enemy[i].rows = 0;
            copy_anima_to_image(map->enemy[i].image, map->image.enemy_a, 0, 0);
        }
    }
    else
    {
        map->enemy[i].image->instances[0].x = next.x * map->scale;
	    map->enemy[i].image->instances[0].y = next.y * map->scale;
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

void enemy_down_up(t_map *map, int i)
{
    t_point cur;
    t_point next;

    cur = map->enemy[i].pos;
    if (map->enemy[i].dir == 'd')
        next = (t_point){cur.x, cur.y + 1};
    else if (map->enemy[i].dir == 'u')
        next = (t_point){cur.x, cur.y - 1};
    if (map->grid[next.y][next.x] == '1' || map->grid[next.y][next.x] == 'C' || map->grid[next.y][next.x] == 'H')
    {
        if (map->enemy[i].dir == 'd')
        {
            map->enemy[i].dir = 'u';
            map->enemy[i].rows = 3;
            copy_anima_to_image(map->enemy[i].image, map->image.enemy_a, 0, 3);
        }
        else if (map->enemy[i].dir == 'u')
        {
            map->enemy[i].dir = 'd';
            map->enemy[i].rows = 2;
            copy_anima_to_image(map->enemy[i].image, map->image.enemy_a, 0, 2);
        }
    }
    else
    {
        map->enemy[i].image->instances[0].x = next.x * map->scale;
	    map->enemy[i].image->instances[0].y = next.y * map->scale;
        map->grid[cur.y][cur.x] = '0';
        map->grid[next.y][next.x] = 'V';
        map->enemy[i].pos = next;
    }
    if (map->enemy[i].pos.x == map->cur.x && map->enemy[i].pos.y == map->cur.y)
    {
        ft_printf("GAME OVER!\n");
		quit_game(map);
    }
}

void enemy_move(t_map *map)
{
    int i;

    i = 0;
    while (i < map->enemy_n)
    {
        if (map->enemy[i].type == 'H')
            enemy_right_left(map, i);
        else if (map->enemy[i].type == 'V')
            enemy_down_up(map, i);
        i++;
    }
}