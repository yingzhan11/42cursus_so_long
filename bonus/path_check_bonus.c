/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:09:04 by yzhan             #+#    #+#             */
/*   Updated: 2024/07/11 16:09:07 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

//func to find a path
static int	find_path(t_map *map, t_point cur, char **matrix)
{
	static int	collect = 0;
	static int	find_exit = 0;

	if (matrix[cur.y][cur.x] == '1')
		return (0);
	else if (matrix[cur.y][cur.x] == 'C')
		collect++;
	else if (matrix[cur.y][cur.x] == 'E')
	{
		map->exit = (t_point){cur.x, cur.y};
		find_exit = 1;
	}
	matrix[cur.y][cur.x] = '1';
	find_path(map, (t_point){cur.x + 1, cur.y}, matrix);
	find_path(map, (t_point){cur.x - 1, cur.y}, matrix);
	find_path(map, (t_point){cur.x, cur.y + 1}, matrix);
	find_path(map, (t_point){cur.x, cur.y - 1}, matrix);
	if (collect == map->collect_all && find_exit == 1)
		return (1);
	return (0);
}

//func to copy a matrix of map grid used to check a valid path
//the valid map must have at least one valid path to win
int	check_path(t_map *map)
{
	char	**matrix;
	int		i;
	int		path;

	i = 0;
	path = 0;
	matrix = malloc((map->row + 1) * (sizeof(char *)));
	if (!matrix)
		error_info(map, "Malloc error when check valid path.");
	while (i < map->row)
	{
		matrix[i] = ft_strdup(map->grid[i]);
		if (!matrix[i])
		{
			delete_matrix(matrix, i);
			error_info(map, "Malloc error when check valid path.");
		}
		i++;
	}
	path = find_path(map, map->start, matrix);
	delete_matrix(matrix, i);
	return (path);
}
