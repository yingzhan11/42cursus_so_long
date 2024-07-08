#include "so_long_bonus.h"



int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t get_pixel(mlx_image_t *image, uint32_t x, uint32_t y)
{
    uint8_t *color;

    if (x > image->width || y > image->height)
        return (0xFF000000);
    color = image->pixels + (y * image->width + x) * sizeof(int32_t);
    return (get_rgba(*(color), *(color + 1), *(color + 2), *(color + 3)));
}

void copy_anima_to_image(mlx_image_t *image, mlx_image_t *anima, uint32_t cols, uint32_t rows)
{
	uint32_t x;
	uint32_t y;
    uint32_t newpixel;

	y = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			newpixel = get_pixel(anima, cols * image->width + x, rows * image->width + y);
			mlx_put_pixel(image, x, y, newpixel);
            x++;
		}
		y++;
	}
}

void enemy_right_left(t_map *map, int i, int j)
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
            map->enemy[i].dir = 'l';
        else if (map->enemy[i].dir == 'l')
            map->enemy[i].dir = 'r';
    }
    else
    {
        map->image.enemy_h->instances[j].x = next.x * map->scale;
	    map->image.enemy_h->instances[j].y = next.y * map->scale;
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

void enemy_down_up(t_map *map, int i, int j)
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
            map->enemy[i].dir = 'u';
        else if (map->enemy[i].dir == 'u')
            map->enemy[i].dir = 'd';
    }
    else
    {
        map->image.enemy_v->instances[j].x = next.x * map->scale;
	    map->image.enemy_v->instances[j].y = next.y * map->scale;
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

void enemy_all(t_map *map)
{
    int i;
    int h;
    int v;

    i = 0;
    h = 0;
    v = 0;
    while (i < map->enemy_n)
    {
        if (map->enemy[i].type == 'H')
        {
            enemy_right_left(map, i, h);
            h++;
        }
        else if (map->enemy[i].type == 'V')
        {
            enemy_down_up(map, i, v);
            v++;
        }
        i++;
    }
}

void enemy_time(t_map *map, int cols)
{
    int i;

    i = 0;
    while (i < map->enemy_n)
    {
        if (map->enemy[i].type == 'H')
            copy_anima_to_image(map->image.enemy_h, map->image.enemy_a, cols, map->enemy[i].rows);
        else if (map->enemy[i].type == 'V')
            copy_anima_to_image(map->image.enemy_v, map->image.enemy_a, cols, map->enemy[i].rows);
        i++;
    }
}

void enemy_move(t_map *map, double newtime)
{
    static double time = 0;
    static int  cols = 0;
    static double flytime = 0;

    flytime += newtime;
    if (cols >= 4)
        cols = 0;
    if (flytime > 0.25)
    {
        enemy_time(map, cols);
        cols++;
        flytime -= 0.25;
    }
    time += newtime;
    if (time > 1)
    {
        enemy_all(map);
        time -= 1;
    }
}