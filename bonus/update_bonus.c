#include "so_long_bonus.h"

static void enemy_animation(t_map *map, int cols)
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

void    player_update(t_map *map, double newtime)
{
    static int  cols = 0;
	static int cols_r = 0;
    static double flytime = 0;

    flytime += newtime;
    if (flytime > 0.25 && map->p_state == 0)
    {
        if (cols >= 4)
			cols = 0;
		copy_anima_to_image(map->player.image, map->image.player_a, cols, map->player.rows);
        cols++;
        flytime -= 0.25;
    }
	if (map->p_state == 1 && flytime > 0.05)
	{
		if (cols_r >= 6)
		{
			cols_r = 0;
		}
		player_move(map, map->player.image, cols_r);
		copy_anima_to_image(map->player.image, map->image.player_run, cols_r, map->player.rows);
		cols_r++;
		flytime -= 0.05;
	}
}
