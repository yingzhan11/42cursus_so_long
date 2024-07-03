# include "so_long.h"

void draw_map(mlx_t *mlx, t_map *map, t_image *image, t_point cur)
{
	int scale;

	scale = map->scale;
	if (map->grid[cur.y][cur.x] == '1')
		mlx_image_to_window(mlx, image->wall, cur.x * scale, cur.y * scale);
	else if (map->grid[cur.y][cur.x] == '0')
		mlx_image_to_window(mlx, image->empty, cur.x * scale, cur.y * scale);
    else if (map->grid[cur.y][cur.x] == 'C')
    {
		mlx_image_to_window(mlx, image->empty, cur.x * scale, cur.y * scale);
		mlx_image_to_window(mlx, image->collect, cur.x * scale, cur.y * scale);
    }
    else if (map->grid[cur.y][cur.x] == 'E')
	{
		mlx_image_to_window(mlx, image->exit2, cur.x * scale, cur.y * scale);
		mlx_image_to_window(mlx, image->exit1, cur.x * scale, cur.y * scale);
		map->exit.x = cur.x;
		map->exit.y = cur.y;
	}
    else if (map->grid[cur.y][cur.x] == 'P')
    {
		mlx_image_to_window(mlx, image->empty, cur.x * scale, cur.y * scale);
		mlx_image_to_window(mlx, image->start, cur.x * scale, cur.y * scale);
        map->start.x = cur.x;
		map->start.y = cur.y;
    }
}

//draw map, except player, record exit, start xy
void image_draw(mlx_t *mlx, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			draw_map(mlx, map, &map->image, (t_point){x, y});
			x++;
		}
		y++;
	}
	map->cur = map->start;
	x = map->start.x;
	y = map->start.y;
	mlx_image_to_window(mlx, map->image.player, x * map->scale, y * map->scale);
}