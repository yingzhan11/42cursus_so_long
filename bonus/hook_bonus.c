/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:32:15 by yzhan             #+#    #+#             */
/*   Updated: 2024/07/11 15:35:25 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
helper function to get the next position of player and 
move to corresponding row in animation image
*/
static void	update_player_dir(t_map *map, char dir)
{
	if (dir == 'W')
	{
		map->next = (t_point){map->cur.x, map->cur.y - 1};
		map->player.row = 3;
	}
	if (dir == 'S')
	{
		map->next = (t_point){map->cur.x, map->cur.y + 1};
		map->player.row = 0;
	}
	if (dir == 'A')
	{
		map->next = (t_point){map->cur.x - 1, map->cur.y};
		map->player.row = 2;
	}
	if (dir == 'D')
	{
		map->next = (t_point){map->cur.x + 1, map->cur.y};
		map->player.row = 1;
	}
}

//hook for keyboard input
void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_map		*map;
	t_player	player;
	int			col;
	int			row;

	map = (t_map *)param;
	player = map->player;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		quit_game(map, "QUIT GAME.");
	if (ft_strchr(MOVEKEY, keydata.key) && keydata.action == MLX_PRESS
		&& map->p_state == 0)
	{
		map->p_state = 1;
		update_player_dir(map, keydata.key);
	}
	col = player.col;
	row = player.row;
	put_anima(player.image, map->image.player_std, col, row);
}

//hook for resize the window
void	my_resizehook(int32_t width, int32_t height, void *param)
{
	t_map	*map;

	map = (t_map *)param;
	map->window_w = width;
	map->window_h = height;
	if (map->player.image)
		mlx_delete_image(map->mlx, map->player.image);
	delete_enemy(map);
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

//hook for update animation based on time
void	my_updatehook(void *param)
{
	t_map	*map;

	map = (t_map *)param;
	map->time = map->mlx->delta_time;
	enemy_update(map, map->time);
	player_update(map, map->time);
}
