/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:25:06 by yzhan             #+#    #+#             */
/*   Updated: 2024/07/11 15:32:03 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	enemy_go_right(t_map *map, int i)
{
	t_point	cur;
	t_point	next;

	cur = map->enemy[i].pos;
	next = (t_point){cur.x + 1, cur.y};
	if (map->grid[next.y][next.x] == '1' || map->grid[next.y][next.x] == 'C'
		|| map->grid[next.y][next.x] == 'V')
	{
		map->enemy[i].dir = 'l';
		map->enemy[i].row = 1;
		put_anima(map->enemy[i].img, map->image.enemy_fly, 0, 1);
	}
	else
	{
		map->enemy[i].img->instances[0].x = next.x * map->scale;
		map->enemy[i].img->instances[0].y = next.y * map->scale;
		map->grid[cur.y][cur.x] = '0';
		map->grid[next.y][next.x] = 'H';
		map->enemy[i].pos = (t_point){next.x, next.y};
	}
	if (map->enemy[i].pos.x == map->cur.x && map->enemy[i].pos.y == map->cur.y)
		quit_game(map, "GAME OVER!");
}

static void	enemy_go_left(t_map *map, int i)
{
	t_point	cur;
	t_point	next;

	cur = map->enemy[i].pos;
	next = (t_point){cur.x - 1, cur.y};
	if (map->grid[next.y][next.x] == '1' || map->grid[next.y][next.x] == 'C'
		|| map->grid[next.y][next.x] == 'V')
	{
		map->enemy[i].dir = 'r';
		map->enemy[i].row = 0;
		put_anima(map->enemy[i].img, map->image.enemy_fly, 0, 0);
	}
	else
	{
		map->enemy[i].img->instances[0].x = next.x * map->scale;
		map->enemy[i].img->instances[0].y = next.y * map->scale;
		map->grid[cur.y][cur.x] = '0';
		map->grid[next.y][next.x] = 'H';
		map->enemy[i].pos = (t_point){next.x, next.y};
	}
	if (map->enemy[i].pos.x == map->cur.x && map->enemy[i].pos.y == map->cur.y)
		quit_game(map, "GAME OVER!");
}

static void	enemy_go_down(t_map *map, int i)
{
	t_point	cur;
	t_point	next;

	cur = map->enemy[i].pos;
	next = (t_point){cur.x, cur.y + 1};
	if (map->grid[next.y][next.x] == '1' || map->grid[next.y][next.x] == 'C'
		|| map->grid[next.y][next.x] == 'H')
	{
		map->enemy[i].dir = 'u';
		map->enemy[i].row = 3;
		put_anima(map->enemy[i].img, map->image.enemy_fly, 0, 3);
	}
	else
	{
		map->enemy[i].img->instances[0].x = next.x * map->scale;
		map->enemy[i].img->instances[0].y = next.y * map->scale;
		map->grid[cur.y][cur.x] = '0';
		map->grid[next.y][next.x] = 'V';
		map->enemy[i].pos = (t_point){next.x, next.y};
	}
	if (map->enemy[i].pos.x == map->cur.x && map->enemy[i].pos.y == map->cur.y)
		quit_game(map, "GAME OVER!");
}

static void	enemy_go_up(t_map *map, int i)
{
	t_point	cur;
	t_point	next;

	cur = map->enemy[i].pos;
	next = (t_point){cur.x, cur.y - 1};
	if (map->grid[next.y][next.x] == '1' || map->grid[next.y][next.x] == 'C'
		|| map->grid[next.y][next.x] == 'H')
	{
		map->enemy[i].dir = 'd';
		map->enemy[i].row = 2;
		put_anima(map->enemy[i].img, map->image.enemy_fly, 0, 2);
	}
	else
	{
		map->enemy[i].img->instances[0].x = next.x * map->scale;
		map->enemy[i].img->instances[0].y = next.y * map->scale;
		map->grid[cur.y][cur.x] = '0';
		map->grid[next.y][next.x] = 'V';
		map->enemy[i].pos = (t_point){next.x, next.y};
	}
	if (map->enemy[i].pos.x == map->cur.x && map->enemy[i].pos.y == map->cur.y)
		quit_game(map, "GAME OVER!");
}

void	enemy_move(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->enemy_n)
	{
		if (map->enemy[i].dir == 'r')
			enemy_go_right(map, i);
		else if (map->enemy[i].dir == 'l')
			enemy_go_left(map, i);
		else if (map->enemy[i].dir == 'd')
			enemy_go_down(map, i);
		else if (map->enemy[i].dir == 'u')
			enemy_go_up(map, i);
		i++;
	}
}
