#include "so_long_bonus.h"

void put_text_move(t_map *map)
{
	char *move;

	move = ft_itoa(map->move);
	if (map->image.text_move == NULL)
	{
		map->image.text_title = mlx_put_string(map->mlx, "Steps:", 32, 32);
		map->image.text_move = mlx_put_string(map->mlx, move, 96, 32);
		//mlx_resize_image(map->image.text_move, width, height);
		free(move);
		return ;
	}
	if (map->image.text_info != NULL && map->p_state == 1)
	{
		mlx_delete_image(map->mlx, map->image.text_info);
		map->info = NULL;
	}
	mlx_delete_image(map->mlx, map->image.text_move);
	map->image.text_move = mlx_put_string(map->mlx, move, 96, 32);
	free(move);
}

void put_text_info(t_map *map, char *info)
{
	if (map->image.text_info != NULL)
		mlx_delete_image(map->mlx, map->image.text_info);
	if (info)
		map->image.text_info = mlx_put_string(map->mlx, info, 32, 52);
}

void	error_info(t_map *map, char *message)
{
	delete_map(map);
	ft_printf("Error: %s\n", message);
	exit(EXIT_FAILURE);
}

void	quit_game(t_map *map, char *message)
{
	if (map)
		delete_map(map);
	ft_printf("%s\n", message);
	exit(EXIT_SUCCESS);
}
