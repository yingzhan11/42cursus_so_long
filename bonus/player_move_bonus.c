/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:09:22 by yzhan             #+#    #+#             */
/*   Updated: 2024/07/11 16:14:15 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

//check the next position element, if it is wall '1', don''t move to
static int	check_grid_next(t_map *map)
{
	if (map->grid[map->next.y][map->next.x] == '1')
	{
		map->p_state = 0;
		map->info = "No passage! You cannot enter the area ahead.";
		put_text_info(map, map->info);
		return (0);
	}
	return (1);
}

/*
when current position is collect, count it and change the image to disabled.
chenk the num of collect, if already get all collections, show info and 
change the image and mark of exit
*/
static void	get_collect(t_map *map, t_image *image)
{
	size_t	i;

	map->collect_get++;
	map->grid[map->cur.y][map->cur.x] = 'c';
	i = 0;
	while (i < image->collect->count)
	{
		if (image->collect->instances[i].x == map->cur.x * map->scale
			&& image->collect->instances[i].y == map->cur.y * map->scale)
		{
			image->collect->instances[i].enabled = false;
			break ;
		}
		i++;
	}
	if (map->collect_get == map->collect_all)
	{
		map->info = "You've collected all the fries!";
		image->exit1->instances[0].enabled = false;
		map->grid[map->exit.y][map->exit.x] = 'e';
	}
	else
		map->info = "You collect one of the fries!";
	put_text_info(map, map->info);
}

/*
check player current position
check collections, exit and enemy
*/
static void	check_cur_grid(t_map *map)
{
	if (map->grid[map->cur.y][map->cur.x] == 'C')
		get_collect(map, &map->image);
	if (map->grid[map->cur.y][map->cur.x] == 'E')
	{
		map->info = "Can't open! you need to collect all Fries first.";
		put_text_info(map, map->info);
	}
	if (map->grid[map->cur.y][map->cur.x] == 'e')
		quit_game(map, "YOU WIN! \\^o^/");
	if (map->grid[map->cur.y][map->cur.x] == 'H'
		|| map->grid[map->cur.y][map->cur.x] == 'V')
		quit_game(map, "GAME OVER! 〒▽〒");
}

/*
func to move player
check next position, if it is wall, do not move to
if no, move to next grid and change the current coord, update move text
and check cur position elements
*/
void	player_move(t_map *map, mlx_image_t *image, int i)
{
	t_point	m;

	if (check_grid_next(map) == 0)
		return ;
	m.x = (map->next.x - map->cur.x) * (map->scale / 6) * (i + 1);
	m.y = (map->next.y - map->cur.y) * (map->scale / 6) * (i + 1);
	image->instances[0].x = (map->cur.x * map->scale) + m.x;
	image->instances[0].y = (map->cur.y * map->scale) + m.y;
	if (i < 5)
		return ;
	map->move++;
	map->cur = map->next;
	put_text_move(map);
	map->p_state = 0;
	check_cur_grid(map);
}
