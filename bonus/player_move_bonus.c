
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

/*func to move player and check collet and exit
check next, if wall or not
then change the current coord and check collect num and exit*/
void	player_move(t_map *map, mlx_image_t *image, int i)
{
	int	collect;

	if (check_grid_next(map) == 0)
	{
		map->p_state = 0;
		if (map->image.text2 == NULL)
			map->image.text2 = mlx_put_string(map->mlx, "No passage! You cannot enter the area ahead.", 200, 32);
		return ;
	}
	//player_move_anima(map, image);
	int x = (map->next.x - map->cur.x) * (map->scale / 6) * (i + 1);
	int y = (map->next.y - map->cur.y) * (map->scale / 6) * (i + 1);
	image->instances[0].x = (map->cur.x * map->scale) + x;
	image->instances[0].y = (map->cur.y * map->scale) + y;
	if (i < 5)
		return ;
	map->move++;
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
		quit_game(map, "You win!");
	if (map->grid[map->cur.y][map->cur.x] == 'H')
		quit_game(map, "GAME OVER!");
	text_update(map);
}



