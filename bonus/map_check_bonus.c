
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
	int	y;
	int	x;

	y = -1;
	while (++y < map->rows)
	{
		x = -1;
		while (++x < map->cols)
		{
			if (!ft_strchr(ELEMENTS, map->grid[y][x]))
				return (0);
			if (map->grid[y][x] == 'P')
			{
				map->start = (t_point){x, y};
				map->player_n++;
			}
			else if (map->grid[y][x] == 'E')
				map->exit_n++;
			else if (map->grid[y][x] == 'C')
				map->collect_all++;
			else if (map->grid[y][x] == 'H' || map->grid[y][x] == 'V')
				map->enemy_n++;
			else if (map->grid[y][x] == '0')
				map->empty_n++;
		}
	}
	map->empty_n = map->empty_n + map->collect_all + 2;
	if (map->player_n == 1 && map->exit_n == 1 && map->collect_all >= 1)
		return (1);
	return (0);
}

int check_enemy(t_map *map)
{
	int	y;
	int x;
	int i;

	map->enemy = malloc(map->enemy_n * sizeof(t_enemy));
	if (!map->enemy)
		error_info(map, "Failed to get enemy positions.");
	y = -1;
	i = 0;
	while (++y < map->rows)
	{
		x = -1;
		while (++x < map->cols)
		{
			if (map->grid[y][x] == 'H' || (map->grid[y][x] == 'V'))
			{
				map->enemy[i].type = map->grid[y][x];
				map->enemy[i].pos = (t_point){x, y};
				if (map->grid[y][x] == 'H')
					map->enemy[i].dir = 'r';
				if (map->grid[y][x] == 'V')
					map->enemy[i].dir = 'd';
				i++;
			}
		}
	}
	map->enemy_den = map->enemy_n * 100 / map->empty_n;
	if (map->enemy_den > 5)
		return (0);
	return (1);
}

