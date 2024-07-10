
#include "so_long_bonus.h"

//check map shape, only rectangular is valid
int	check_shape(t_map *map)
{
	size_t	len;
	int		y;

	y = 0;
	len = ft_strlen(map->grid[y]);
	while (y < map->rows)
	{
		if (ft_strlen(map->grid[y]) != len)
			return (0);
		y++;
	}
	map->cols = len;
	return (1);
}

//check map boundary, must be closed by the wall '1'
int	check_wall(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->cols)
	{
		if (map->grid[0][i] != '1' || map->grid[map->rows - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < map->rows)
	{
		if (map->grid[i][0] != '1' || map->grid[i][map->cols - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

//check map elements, only '01CEP' is valid, and only one 'EPC' is valid
int	check_elements(t_map *map)
{
	t_point p;

	p.y = 0;
	while (p.y < map->rows)
	{
		p.x = 0;
		while (p.x < map->cols)
		{
			if (!ft_strchr(ELEMENTS, map->grid[p.y][p.x]))
				return (0);
			if (map->grid[p.y][p.x] == 'P')
				map->player_n++;
			else if (map->grid[p.y][p.x] == 'E')
				map->exit_n++;
			else if (map->grid[p.y][p.x] == 'C')
				map->collect_all++;
			else if (map->grid[p.y][p.x] == 'H' || map->grid[p.y][p.x] == 'V')
				map->enemy_n++;
			p.x++;
		}
		p.y++;
	}
	if (map->player_n == 1 && map->exit_n == 1 && map->collect_all >= 1)
		return (1);
	return (0);
}

void get_player_position(t_map *map)
{
	t_point p;

	p.y = 0;
	while (p.y < map->rows)
	{
		p.x = 0;
		while (++p.x < map->cols)
		{
			if (map->grid[p.y][p.x] == 'P')
			{
				map->start = (t_point){p.x, p.y};
				return ;
			}
			p.x++;
		}
		p.y++;
	}

}

void get_enemy_path(t_map *map)
{
	t_point p;
	int i;

	map->enemy = malloc(map->enemy_n * sizeof(t_enemy));
	if (!map->enemy)
		error_info(map, "Failed to get enemy positions.");
	p.y = -1;
	i = 0;
	while (++p.y < map->rows && i < map->enemy_n)
	{
		p.x = -1;
		while (++p.x < map->cols)
		{
			if (map->grid[p.y][p.x] == 'H' || (map->grid[p.y][p.x] == 'V'))
			{
				map->enemy[i].type = map->grid[p.y][p.x];
				map->enemy[i].pos = (t_point){p.x, p.y};
				if (map->grid[p.y][p.x] == 'H')
					map->enemy[i].dir = 'r';
				if (map->grid[p.y][p.x] == 'V')
					map->enemy[i].dir = 'd';
				i++;
			}
		}
	}
}

