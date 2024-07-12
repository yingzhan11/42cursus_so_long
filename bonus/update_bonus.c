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
	static double	fly_time = 0;
	static double	move_time = 0;
	static int		col = 0;

	fly_time += newtime;
	if (col >= 4)
		col = 0;
	if (fly_time > 0.25)
	{
		enemy_animation(map, col);
		col++;
		fly_time -= 0.25;
	}
	move_time += newtime;
	if (move_time > ENEMY_SPEED)
	{
		enemy_move(map);
		move_time -= ENEMY_SPEED;
	}
}

void	player_update(t_map *map, double newtime)
{
	t_player		player;
	static double	std_time = 0;
	static double   run_time = 0;
	static int		col = 0;
	static int		col_r = 0;

	std_time += newtime;
	player = map->player;
	if (std_time > 0.25 && map->p_state == 0)
	{
		if (col >= 4)
			col = 0;
		put_anima(player.image, map->image.player_std, col++, player.row);
		std_time -= 0.25;
	}
	run_time += newtime;
	if (map->p_state == 1 && run_time > PLAYER_SPEED)
	{
		if (col_r >= 6)
			col_r = 0;
		player_move(map, player.image, col_r);
		put_anima(player.image, map->image.player_run, col_r++, player.row);
		run_time -= PLAYER_SPEED;
	}
}
