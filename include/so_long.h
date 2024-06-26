#ifndef SO_LONG_H
# define SO_LONG_H

# include <MLX42/MLX42.h>
# include <libft.h>
# include <ft_printf/ft_printf.h>
# include <get_next_line/get_next_line.h>

# include <fcntl.h>
# include <stdio.h>

typedef struct s_coord
{
    int     x;
    int     y;
}   t_coord;

typedef struct s_image
{
    int image_w;
    int image_h;
    int size;
    mlx_image_t *empty;
    mlx_image_t *wall;
    mlx_image_t *collect;
    mlx_image_t *exit;
    mlx_image_t *start;
    mlx_image_t *player;
}   t_image;

typedef struct s_map
{
    char    *filename;
    char     **grid; //map
    int     rows; //y
    int     cols; //x
    //mlx size
    int     window_w;
    int     window_h;
    
    //exit
    t_coord     exit;
    //start
    t_coord     start;
    
}   t_map;



void map_initialize(t_map *map);
void    error_info(char *message);
void image_initialize(mlx_t *mlx, t_map *map, t_image *image);
void image_draw(mlx_t *mlx, t_map *map, t_image *image);

#endif