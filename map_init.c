/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:14:00 by yzhan             #+#    #+#             */
/*   Updated: 2024/07/04 11:47:24 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//check file is valid or not, filename is *.ber
static void	file_check(t_map *map, char *filename)
{
	int	length;
	int	fd;

	if (!filename)
		error_info(map, "NULL filname of map!");
	length = ft_strlen(filename);
	if (ft_strncmp(&filename[length - 4], ".ber", 4))
		error_info(map, "Map name is not '*.ber'!");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_info(map, "Failed to open map file!");
	close (fd);
}

//count the rows in map grid
static void	count_rows(t_map *map, char *filename)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_info(map, "Failed to open map file!");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map->rows++;
		free (line);
	}
	close (fd);
}

//read the map file and convert it into a char grid
static void	read_map(t_map *map, char *filename)
{
	char	*line;
	int		y;
	int		fd;

	count_rows(map, filename);
	map->grid = malloc((map->rows + 1) * sizeof(char *));
	if (map->grid == NULL)
		error_info(map, "Failed to create map grid!");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_info(map, "Failed to open map file!");
	y = 0;
	while (y < map->rows)
	{
		line = get_next_line(fd);
		if (!line)
			error_info(map, "Failed to get cols from map file.");
		map->grid[y] = ft_strtrim(line, "\n");
		if (!map->grid[y])
			error_info(map, "Failed to create column in map grid.");
		y++;
		free(line);
	}
	close(fd);
}

/*
read the map file and check if the map is valid or not.
check map elements '01CEP', the shape and size of map,
the boundary and the path
*/
void	map_initialize(t_map *map, char *filename)
{
	file_check(map, filename);
	read_map(map, filename);
	if (map->rows == 0)
		error_info(map, "Map is empty.");
	if (check_shape(map) == 0)
		error_info(map, "Map is not a rectangular.");
	if (map->rows > 120 || map->cols > 120)
		error_info(map, "This map is too big.");
	if (check_elements(map) == 0)
		error_info(map, "Elements of map is invalid.");
	if (check_wall(map) == 0)
		error_info(map, "The map is not closed by walls.");
	if (check_path(map) == 0)
		error_info(map, "Can't find a valid path on this map.");
	map->cur = (t_point){map->start.x, map->start.y};
}
