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

#include "so_long_bonus.h"

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

/*void player_move_anima(t_map *map, mlx_image_t *image)
{
	copy_anima_to_image(map->player.image, map->image.player_run, 0, 0);
	map->player.cols = 0;

	// Calculate movement step for smooth animation
    int steps = 10; // Number of steps for smooth movement
    int dx = map->next.x - map->cur.x;
    int dy = map->next.y - map->cur.y;
    float stepX = (float)dx / steps;
    float stepY = (float)dy / steps;
	// Perform smooth movement with animation update
    for (int i = 0; i <= steps; ++i)
    {
        image->instances[0].x = (map->cur.x + stepX * i) * map->scale;
        image->instances[0].y = (map->cur.y + stepY * i) * map->scale;
		ft_printf("%d, %d\n", image->instances[0].x, image->instances[0].y);
        // Update animation every step
        player_update(map, 0.025); // Adjust timing for smooth animation
		
        // Redraw image
        //image_draw(map->mlx, map);

        // Wait or use a delay function to control animation speed
        // You can use usleep or similar to add a slight delay if needed
        usleep(50000); // 50ms delay
    }
}*/

/*func to move player and check collet and exit
check next, if wall or not
then change the current coord and check collect num and exit*/
void	player_move(t_map *map, mlx_image_t *image, int i)
{
	int	collect;

	if (check_grid_next(map) == 0)
	{
		map->p_state = 0;
		return ;
	}
	//player_move_anima(map, image);
	int x = (map->next.x - map->cur.x) * (map->scale / 6) * (i + 1);
	int y = (map->next.y - map->cur.y) * (map->scale / 6) * (i + 1);
	image->instances[0].x = (map->cur.x * map->scale) + x;
	image->instances[0].y = (map->cur.y * map->scale) + y;
	if (i < 5)
	{
		return ;
	}
	
	map->move++;
	ft_printf("Steps count: %d\n", map->move);
	map->cur = map->next;
	map->p_state = 0;

	if (map->grid[map->cur.y][map->cur.x] == 'C')
		get_collect(map, &map->image);
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
	if (map->grid[map->cur.y][map->cur.x] == 'H')
	{
		ft_printf("GAME OVER!\n");
		quit_game(map);
	}
}



void player_update(t_map *map, double newtime)
{
    static int  cols = 0;
	static int cols_r = 0;
    static double flytime = 0;

    flytime += newtime;
   
    if (flytime > 0.25 && map->p_state == 0)
    {
        if (cols >= 4)
			cols = 0;
		copy_anima_to_image(map->player.image, map->image.player_a, cols, map->player.rows);
        cols++;
        flytime -= 0.25;
    }
	if (map->p_state == 1 && flytime > 0.05)
	{
		if (cols_r >= 6)
		{
			cols_r = 0;
		}
		player_move(map, map->player.image, cols_r);
		copy_anima_to_image(map->player.image, map->image.player_run, cols_r, map->player.rows);
		
		cols_r++;
		flytime -= 0.05;
	}
}