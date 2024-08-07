/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:46:10 by yzhan             #+#    #+#             */
/*   Updated: 2024/07/04 09:51:40 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//hook for keyboard input
void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = (t_map *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		quit_game(map);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		map->next = (t_point){map->cur.x, map->cur.y - 1};
		player_move(map, &map->image);
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		map->next = (t_point){map->cur.x, map->cur.y + 1};
		player_move(map, &map->image);
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		map->next = (t_point){map->cur.x - 1, map->cur.y};
		player_move(map, &map->image);
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		map->next = (t_point){map->cur.x + 1, map->cur.y};
		player_move(map, &map->image);
	}
}

//hook for resize the window
void	my_resizehook(int32_t width, int32_t height, void *param)
{
	t_map	*map;

	map = (t_map *)param;
	map->window_w = width;
	map->window_h = height;
	delete_image(map);
	image_initialize(map->mlx, map);
	image_draw(map->mlx, map);
}

//hook for close the window
void	my_closehook(void *param)
{
	t_map	*map;

	map = (t_map *)param;
	delete_map(map);
	exit(EXIT_SUCCESS);
}
