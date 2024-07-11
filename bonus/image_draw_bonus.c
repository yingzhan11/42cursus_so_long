/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_draw_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:36:14 by yzhan             #+#    #+#             */
/*   Updated: 2024/07/11 15:52:00 by yzhan            ###   ########.fr       */
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

static void	draw_enemy(mlx_t *mlx, t_map *map, t_image *image, t_enemy *enemy)
{
	int	i;
	int	x;
	int	y;
	int	col;
	int	row;

	i = 0;
	while (i < map->enemy_n)
	{
		x = enemy[i].pos.x;
		y = enemy[i].pos.y;
		if (enemy[i].type == 'H' && enemy[i].dir == 'r')
			enemy[i].row = 0;
		if (enemy[i].type == 'H' && enemy[i].dir == 'l')
			enemy[i].row = 1;
		if (enemy[i].type == 'V' && enemy[i].dir == 'd')
			enemy[i].row = 2;
		if (enemy[i].type == 'V' && enemy[i].dir == 'u')
			enemy[i].row = 3;
		col = enemy[i].col;
		row = enemy[i].row;
		put_anima(enemy[i].img, image->enemy_fly, col, row);
		mlx_image_to_window(mlx, enemy[i].img, x * map->scale, y * map->scale);
		i++;
	}
}

//draw map to window, then get the player position and put the player image
void	image_draw(mlx_t *mlx, t_map *map)
{
	int			x;
	int			y;
	t_player	player;

	y = 0;
	while (y < map->row)
	{
		x = 0;
		while (x < map->col)
		{
			draw_map(mlx, map, &map->image, (t_point){x, y});
			x++;
		}
		y++;
	}
	draw_enemy(mlx, map, &map->image, map->enemy);
	x = map->cur.x;
	y = map->cur.y;
	player = map->player;
	put_anima(player.image, map->image.player_std, player.col, player.row);
	mlx_image_to_window(mlx, map->player.image, x * map->scale, y * map->scale);
	put_text_move(map);
	if (map->info)
		put_text_info(map, map->info);
}
