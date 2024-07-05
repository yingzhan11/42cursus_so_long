/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:52:24 by yzhan             #+#    #+#             */
/*   Updated: 2024/07/04 10:18:44 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

//draw images to window based on the map grid, except player image
static void	draw_map(mlx_t *mlx, t_map *map, t_image *image, t_point cur)
{
	int	scale;

	scale = map->scale;
	if (map->grid[cur.y][cur.x] == '1')
		mlx_image_to_window(mlx, image->wall, cur.x * scale, cur.y * scale);
	else if (map->grid[cur.y][cur.x] == '0' || map->grid[cur.y][cur.x] == 'H')
		mlx_image_to_window(mlx, image->empty, cur.x * scale, cur.y * scale);
	else if (map->grid[cur.y][cur.x] == 'C')
	{
		mlx_image_to_window(mlx, image->empty, cur.x * scale, cur.y * scale);
		mlx_image_to_window(mlx, image->collect, cur.x * scale, cur.y * scale);
	}
	else if (map->grid[cur.y][cur.x] == 'c')
		mlx_image_to_window(mlx, image->empty, cur.x * scale, cur.y * scale);
	else if (map->grid[cur.y][cur.x] == 'E')
	{
		mlx_image_to_window(mlx, image->exit2, cur.x * scale, cur.y * scale);
		mlx_image_to_window(mlx, image->exit1, cur.x * scale, cur.y * scale);
	}
	else if (map->grid[cur.y][cur.x] == 'e')
		mlx_image_to_window(mlx, image->exit2, cur.x * scale, cur.y * scale);
	else if (map->grid[cur.y][cur.x] == 'P')
		mlx_image_to_window(mlx, image->start, cur.x * scale, cur.y * scale);
}

//draw map to window, then get the player position and put the player image
void	image_draw(mlx_t *mlx, t_map *map)
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
	//draw enemy
	x = map->enemy_sp.x;
	y = map->enemy_sp.y;
	mlx_image_to_window(mlx, map->image.enemy, x * map->scale, y * map->scale);
	x = map->cur.x;
	y = map->cur.y;
	mlx_image_to_window(mlx, map->image.player, x * map->scale, y * map->scale);
}
