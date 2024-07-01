# include "so_long.h"

void image_size(t_map *map, t_image *image)
{
    image->image_w = map->window_w / map->cols;
    image->image_h = map->window_h / map->rows;
    if (image->image_w <= image->image_h)
        map->scale = image->image_w;
    else
        map->scale = image->image_h;
}

mlx_image_t *image_load(mlx_t *mlx, t_map *map, const char *path)
{
    mlx_texture_t *texture;
    mlx_image_t *image;

    //load texture
    texture = mlx_load_png(path);
    //texture to image
    image = mlx_texture_to_image(mlx, texture);
    //delete texture
    mlx_delete_texture(texture);
    //resize image
    mlx_resize_image(image, map->scale, map->scale);
    return(image);
}

void image_initialize(mlx_t *mlx, t_map *map, t_image *image)
{
    //check image size
    image_size(map, image);
    //load image
    image->empty = image_load(mlx, map, "./textures/Empty.png");
    image->wall = image_load(mlx, map, "./textures/Wall.png");
    image->collect = image_load(mlx, map, "./textures/Collect.png");
    image->exit1 = image_load(mlx, map, "./textures/Door1.png");
    image->exit2 = image_load(mlx, map, "./textures/Door2.png");
    image->start = image_load(mlx, map, "./textures/Start.png");
    image->player = image_load(mlx, map, "./textures/Player_One.png");
	
	
}