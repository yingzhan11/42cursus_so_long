/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:03:40 by yzhan             #+#    #+#             */
/*   Updated: 2024/07/04 12:06:20 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
	if (map->image.player_a)
		mlx_delete_image(map->mlx, map->image.player_a);
	if (map->image.enemy_a)
		mlx_delete_image(map->mlx, map->image.enemy_a);
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
	delete_image(map);
	if (map->grid)
		delete_matrix(map->grid, map->rows);
	if (map->enemy)
		free(map->enemy);
	if (map->mlx)
		mlx_terminate(map->mlx);
}

void	quit_game(t_map *map)
{
	if (map)
		delete_map(map);
	exit(EXIT_SUCCESS);
}

void	error_info(t_map *map, char *message)
{
	delete_map(map);
	ft_printf("Error: %s\n", message);
	exit(EXIT_FAILURE);
}
