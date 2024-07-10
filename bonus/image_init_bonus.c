
#include "so_long_bonus.h"

//calculate the image size according to the window size
static void	image_size(t_map *map)
{
	map->image.image_w = map->window_w / map->cols;
	map->image.image_h = map->window_h / map->rows;
	if (map->image.image_w <= map->image.image_h)
		map->scale = map->image.image_w;
	else
		map->scale = map->image.image_h;
	//map->text_scale = map->scale / 24;
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


static mlx_image_t *animation_load(mlx_t *mlx, t_map *map, const char *path, int cols, int rows)
{	
	mlx_texture_t	*texture;
	mlx_image_t	*anima;

	texture = mlx_load_png(path);
	if (!texture)
		error_info(map, "Fail to load animation2.");
	anima = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	mlx_resize_image(anima, map->scale * cols, map->scale * rows);
	return (anima);
}

//calculate image size & load image
void	image_initialize(mlx_t *mlx, t_map *map)
{
	int i;

	image_size(map);
	map->image.empty = image_load(mlx, map, "./textures/bonus/empty.png");
	map->image.wall = image_load(mlx, map, "./textures/bonus/wall.png");
	map->image.collect = image_load(mlx, map, "./textures/bonus/collect.png");
	map->image.exit1 = image_load(mlx, map, "./textures/bonus/exit_close.png");
	map->image.exit2 = image_load(mlx, map, "./textures/bonus/exit_open.png");
	map->image.start = image_load(mlx, map, "./textures/bonus/start.png");
	map->image.player_std = animation_load(mlx, map, "./textures/bonus/player_stand.png", 4, 4);
	map->image.player_run = animation_load(mlx, map, "./textures/bonus/player_run.png", 6, 4);
	map->image.text_title = NULL;
	map->image.text_move = NULL;
	map->image.text_info = NULL;
	map->player.image = mlx_new_image(mlx, map->scale, map->scale);
	map->image.enemy_fly = animation_load(mlx, map, "./textures/bonus/enemy.png", 4, 4);
	i = -1;
	while (++i < map->enemy_n)
		map->enemy[i].image = mlx_new_image(mlx, map->scale, map->scale);
}
