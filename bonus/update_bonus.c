/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:52:02 by yzhan             #+#    #+#             */
/*   Updated: 2024/07/11 16:59:59 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	enemy_animation(t_map *map, int col)
{
	int		i;
	t_enemy	enemy;

	i = 0;
	while (i < map->enemy_n)
	{
		enemy = map->enemy[i];
		put_anima(enemy.img, map->image.enemy_fly, col, enemy.row);
		i++;
	}
}

void	enemy_update(t_map *map, double newtime)
{
	static double	time = 0;
	static int		col = 0;
	static double	flytime = 0;

	flytime += newtime;
	if (col >= 4)
		col = 0;
	if (flytime > 0.25)
	{
		enemy_animation(map, col);
		col++;
		flytime -= 0.25;
	}
	time += newtime;
	if (time > 1)
	{
		enemy_move(map);
		time -= 1;
	}
}

void	player_update(t_map *map, double newtime)
{
	static int		col = 0;
	static int		cols_r = 0;
	static double	flytime = 0;
	t_player		player;

	flytime += newtime;
	player = map->player;
	if (flytime > 0.25 && map->p_state == 0)
	{
		if (col >= 4)
			col = 0;
		put_anima(player.image, map->image.player_std, col, player.row);
		col++;
		flytime -= 0.25;
	}
	if (map->p_state == 1 && flytime > 0.05)
	{
		if (cols_r >= 6)
			cols_r = 0;
		player_move(map, player.image, cols_r);
		put_anima(player.image, map->image.player_run, cols_r, player.row);
		cols_r++;
		flytime -= 0.05;
	}
}
