/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:23:12 by yzhan             #+#    #+#             */
/*   Updated: 2024/07/04 10:28:11 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//check the number of input parameter, only 1 param is valid
static void	param_check(int argc)
{
	if (argc <= 1)
	{
		ft_printf("Please load one *.ber map file after './so_long '\n");
		exit (EXIT_FAILURE);
	}
	else if (argc > 2)
	{
		ft_printf("Too many files! Only one each time!\n");
		exit (EXIT_FAILURE);
	}
}

//calculate the window size based on cols and rows of map grid and init window
static void	window_initialize(t_map *map)
{
	int	scale;
	int	x;
	int	y;

	x = map->cols / 16;
	y = map->rows / 16;
	if (x >= y)
		scale = 160 / (x + 1);
	else
		scale = 160 / (y + 1);
	map->window_w = map->cols * scale;
	map->window_h = map->rows * scale;
	map->mlx = mlx_init(map->window_w, map->window_h, "so_long", true);
	if (!map->mlx)
		error_info(map, "Fail to initialize window");
}

int	main(int argc, char **argv)
{
	t_map	map;

	ft_bzero(&map, sizeof(t_map));
	param_check(argc);
	map_initialize(&map, argv[1]);
	window_initialize(&map);
	image_initialize(map.mlx, &map);
	image_draw(map.mlx, &map);
	mlx_key_hook(map.mlx, my_keyhook, &map);
	mlx_resize_hook(map.mlx, my_resizehook, &map);
	mlx_close_hook(map.mlx, my_closehook, &map);
	mlx_loop(map.mlx);
	mlx_terminate(map.mlx);
	return (EXIT_SUCCESS);
}
