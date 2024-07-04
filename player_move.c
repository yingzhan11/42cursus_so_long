/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:48:51 by yzhan             #+#    #+#             */
/*   Updated: 2024/07/04 12:03:29 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//check the next position element, if it is wall '1', don''t move to
static int	check_grid_next(t_map *map)
{
	if (map->grid[map->next.y][map->next.x] == '1')
	{
		ft_printf("No passage! You cannot enter the area ahead.\n");
		return (0);
	}
	return (1);
}

/*when current position is collect, count it and change the image to empty.
chenk the num of collect, if already get all collections,
show info and change the image of exit*/
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
		ft_printf("You've collected all the fries!\n");
		image->exit1->instances[0].enabled = false;
		map->grid[map->exit.y][map->exit.x] = 'e';
	}
	else
		ft_printf("Found Fries: %d/%d\n", map->collect_get, map->collect_all);
}

/*func to move player and check collet and exit
check next, if wall or not
then change the current coord and check collect num and exit*/
void	player_move(t_map *map, t_image *image)
{
	int	collect;

	if (check_grid_next(map) == 0)
		return ;
	image->player->instances[0].x = map->next.x * map->scale;
	image->player->instances[0].y = map->next.y * map->scale;
	map->move++;
	ft_printf("Steps count: %d\n", map->move);
	map->cur = map->next;
	if (map->grid[map->cur.y][map->cur.x] == 'C')
		get_collect(map, image);
	collect = map->collect_get;
	if (map->grid[map->cur.y][map->cur.x] == 'E')
	{
		ft_printf("Can't open! you need to collect all Fries first.\n");
		ft_printf("Current Fries: %d/%d\n", collect, map->collect_all);
	}
	if (map->grid[map->cur.y][map->cur.x] == 'e')
	{
		ft_printf("You win!\n");
		quit_game(map);
	}
}
