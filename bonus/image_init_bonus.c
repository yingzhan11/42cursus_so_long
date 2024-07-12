/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:56:35 by yzhan             #+#    #+#             */
/*   Updated: 2024/07/11 16:06:10 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

//calculate the image size according to the window size
static void	image_size(t_map *map)
{
	map->image.image_w = map->window_w / map->col;
	map->image.image_h = map->window_h / map->row;
	if (map->image.image_w <= map->image.image_h)
		map->scale = map->image.image_w;
	else
		map->scale = map->image.image_h;
}

//load texture, convert texture to image, then delete texture and resize image
static mlx_image_t	*image_load(mlx_t *mlx, t_map *map, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	image = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	mlx_resize_image(image, map->scale, map->scale);
	return (image);
}

static	mlx_image_t	*ani_load(t_map *map, const char *path, int col, int row)
{	
	mlx_texture_t	*texture;
	mlx_image_t		*anima;

	texture = mlx_load_png(path);
	if (!texture)
		error_info(map, "Fail to load animation2.");
	anima = mlx_texture_to_image(map->mlx, texture);
	mlx_delete_texture(texture);
	mlx_resize_image(anima, map->scale * col, map->scale * row);
	return (anima);
}

//calculate image size & load image
void	image_initialize(mlx_t *mlx, t_map *map)
{
	int	i;

	image_size(map);
	map->image.empty = image_load(mlx, map, "./textures/empty.png");
	map->image.wall = image_load(mlx, map, "./textures/wall.png");
	map->image.collect = image_load(mlx, map, "./textures/collect.png");
	map->image.exit1 = image_load(mlx, map, "./textures/exit_close.png");
	map->image.exit2 = image_load(mlx, map, "./textures/exit_open.png");
	map->image.start = image_load(mlx, map, "./textures/start.png");
	map->image.player_std = ani_load(map, "./textures/p_stand.png", 4, 4);
	map->image.player_run = ani_load(map, "./textures/p_run.png", 6, 4);
	map->image.text_title = NULL;
	map->image.text_move = NULL;
	map->image.text_info = NULL;
	map->player.image = mlx_new_image(mlx, map->scale, map->scale);
	map->image.enemy_fly = ani_load(map, "./textures/enemy.png", 4, 4);
	i = 0;
	while (i < map->enemy_n)
	{
		map->enemy[i].img = mlx_new_image(mlx, map->scale, map->scale);
		i++;
	}
}
