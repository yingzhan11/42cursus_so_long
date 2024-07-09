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
	else if (map->grid[cur.y][cur.x] == 'P')
		mlx_image_to_window(mlx, image->start, cur.x * scale, cur.y * scale);
	else
		mlx_image_to_window(mlx, image->empty, cur.x * scale, cur.y * scale);
	if (map->grid[cur.y][cur.x] == 'C')
		mlx_image_to_window(mlx, image->collect, cur.x * scale, cur.y * scale);
	else if (map->grid[cur.y][cur.x] == 'E')
	{
		mlx_image_to_window(mlx, image->exit2, cur.x * scale, cur.y * scale);
		mlx_image_to_window(mlx, image->exit1, cur.x * scale, cur.y * scale);
	}
	else if (map->grid[cur.y][cur.x] == 'e')
		mlx_image_to_window(mlx, image->exit2, cur.x * scale, cur.y * scale);
}



void draw_enemy(mlx_t *mlx, t_map *map, t_image *image, t_enemy *enemy)
{
	int i;
	int	x;
	int	y;

	i = 0;
	while (i < map->enemy_n)
	{
		x = enemy[i].pos.x;
		y = enemy[i].pos.y;
		if (enemy[i].type == 'H')
		{
			copy_anima_to_image(enemy[i].image, image->enemy_a, 0, 0);
			enemy[i].cols = 0;
			enemy[i].rows = 0;
		}
		if (enemy[i].type == 'V')
		{
			copy_anima_to_image(enemy[i].image, image->enemy_a, 0, 2);
			enemy[i].cols = 0;
			enemy[i].rows = 2;
		}
		mlx_image_to_window(mlx, enemy[i].image, x * map->scale, y * map->scale);
		i++;
	}
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
	draw_enemy(mlx, map, &map->image, map->enemy);
	//draw player
	x = map->cur.x;
	y = map->cur.y;
	copy_anima_to_image(map->player.image, map->image.player_a, 0, 0);
	map->player.cols = 0;
	map->player.rows = 0;
	mlx_image_to_window(mlx, map->player.image, x * map->scale, y * map->scale);
}
