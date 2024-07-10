#include "so_long_bonus.h"

void text_update(t_map *map)
{
	char *move;
	//int i;

	move = ft_itoa(map->move);
	if (map->image.text == NULL)
	{
		map->image.text_title = mlx_put_string(map->mlx, "Steps:", 32, 32);
		//mlx_resize_image(map->image.text_title, map->image.text_title->width * map->text_scale, map->image.text_title->height * map->text_scale);
		map->image.text = mlx_put_string(map->mlx, move, 96, 32);
		//mlx_resize_image(map->image.text, map->image.text->width * map->text_scale, map->image.text->height * map->text_scale);
		free(move);
		return ;
	}
	if (map->image.text2 != NULL)
	{
		mlx_delete_image(map->mlx, map->image.text2);
		map->image.text2 = NULL;
	}
	mlx_delete_image(map->mlx, map->image.text);
	map->image.text = mlx_put_string(map->mlx, move, 96, 32);
	//mlx_resize_image(map->image.text, map->image.text->width * map->text_scale, map->image.text->height * map->text_scale);
	free(move);
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