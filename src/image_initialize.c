# include "so_long.h"

void image_size(t_map *map, t_image *image)
{
    image->image_w = map->window_w / map->cols;
    image->image_h = map->window_h / map->rows;
    if (image->image_w <= image->image_h)
        image->size = image->image_w;
    else
        image->size = image->image_h;
}

mlx_image_t *image_load(mlx_t *mlx, t_image *image, const char *path)
{
    mlx_texture_t *tex;
    mlx_image_t *img;

    //load texture
    tex = mlx_load_png(path);
    //texture to image
    img = mlx_texture_to_image(mlx, tex);
    //delete texture
    mlx_delete_texture(tex);
    //resize image
    mlx_resize_image(img, image->size, image->size);
    return(img);
}

void image_initialize(mlx_t *mlx, t_map *map, t_image *image)
{
    //check image size
    image_size(map, image);
    //load image
    image->empty = image_load(mlx, image, "./textures/Empty.png");
    image->wall = image_load(mlx, image, "./textures/Wall.png");
    image->collect = image_load(mlx, image, "./textures/Collect.png");
    image->exit = image_load(mlx, image, "./textures/Exit.png");
    image->start = image_load(mlx, image, "./textures/Start.png");
    image->player = image_load(mlx, image, "./textures/Player_One.png");
	
	
}