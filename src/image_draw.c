# include "so_long.h"

void draw_map(mlx_t *mlx, t_map *map, t_image *image, t_coord cur)
{
	int size;

	size = image->size;
	if (map->grid[cur.y][cur.x] == '1')
		mlx_image_to_window(mlx, image->wall, cur.x * size, cur.y * size);
	else if (map->grid[cur.y][cur.x] == '0')
		mlx_image_to_window(mlx, image->empty, cur.x * size, cur.y * size);
    else if (map->grid[cur.y][cur.x] == 'C')
    {
        mlx_image_to_window(mlx, image->empty, cur.x * size, cur.y * size);
		mlx_image_to_window(mlx, image->collect, cur.x * size, cur.y * size);
    }
    else if (map->grid[cur.y][cur.x] == 'E')
	{
		mlx_image_to_window(mlx, image->empty, cur.x * size, cur.y * size);
		mlx_image_to_window(mlx, image->exit, cur.x * size, cur.y * size);
		map->exit.x = cur.x;
		map->exit.y = cur.y;
	}
    else if (map->grid[cur.y][cur.x] == 'P')
    {
		mlx_image_to_window(mlx, image->empty, cur.x * size, cur.y * size);
		mlx_image_to_window(mlx, image->start, cur.x * size, cur.y * size);
        map->start.x = cur.x;
		map->start.y = cur.y;
    }
}

void image_draw(mlx_t *mlx, t_map *map, t_image *image)
{
    //draw map, except player, record exit, start xy
	t_coord cur;

	cur.y = 0;
	while (cur.y < map->rows)
	{
		cur.x = 0;
		while (cur.x < map->cols)
		{
			draw_map(mlx, map, image, cur);
			cur.x++;
		}
		cur.y++;
	}
    //put player
	cur = map->start;
	mlx_image_to_window(mlx, image->player, (cur.x + 1) * image->size, (cur.y + 1) * image->size);
}