#include "so_long_bonus.h"

void enemy_animation(t_map *map, int cols)
{
    int i;

    i = 0;
    while (i < map->enemy_n)
    {
        copy_anima_to_image(map->enemy[i].image, map->image.enemy_a, cols, map->enemy[i].rows);
        i++;
    }
}

void enemy_update(t_map *map, double newtime)
{
    static double time = 0;
    static int  cols = 0;
    static double flytime = 0;

    flytime += newtime;
    if (cols >= 4)
        cols = 0;
    if (flytime > 0.25)
    {
        enemy_animation(map, cols);
        cols++;
        flytime -= 0.25;
    }
    time += newtime;
    if (time > 1)
    {
        enemy_move(map);
        time -= 1;
    }
}