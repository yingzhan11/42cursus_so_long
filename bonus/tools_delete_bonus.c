/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_delete_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:50:28 by yzhan             #+#    #+#             */
/*   Updated: 2024/07/11 16:51:00 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	delete_enemy(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->enemy_n)
	{
		if (map->enemy[i].img)
			mlx_delete_image(map->mlx, map->enemy[i].img);
		i++;
	}
}

void	delete_image(t_map *map)
{
	if (map->image.empty)
		mlx_delete_image(map->mlx, map->image.empty);
	if (map->image.wall)
		mlx_delete_image(map->mlx, map->image.wall);
	if (map->image.collect)
		mlx_delete_image(map->mlx, map->image.collect);
	if (map->image.exit1)
		mlx_delete_image(map->mlx, map->image.exit1);
	if (map->image.exit2)
		mlx_delete_image(map->mlx, map->image.exit2);
	if (map->image.start)
		mlx_delete_image(map->mlx, map->image.start);
	if (map->image.player_std)
		mlx_delete_image(map->mlx, map->image.player_std);
	if (map->image.player_run)
		mlx_delete_image(map->mlx, map->image.player_run);
	if (map->image.enemy_fly)
		mlx_delete_image(map->mlx, map->image.enemy_fly);
	if (map->image.text_title)
		mlx_delete_image(map->mlx, map->image.text_title);
	if (map->image.text_move)
		mlx_delete_image(map->mlx, map->image.text_move);
	if (map->image.text_info)
		mlx_delete_image(map->mlx, map->image.text_info);
}

void	delete_matrix(char **matrix, int i)
{
	int	y;

	y = 0;
	if (!matrix)
		return ;
	while (y < i)
	{
		free (matrix[y]);
		y++;
	}
	free (matrix);
}

void	delete_map(t_map *map)
{
	if (!map)
		return ;
	if (map->enemy)
		delete_enemy(map);
	if (map->player.image)
		mlx_delete_image(map->mlx, map->player.image);
	delete_image(map);
	if (map->grid)
		delete_matrix(map->grid, map->row);
	if (map->enemy)
		free(map->enemy);
	if (map->mlx)
		mlx_terminate(map->mlx);
}
