#ifndef SO_LONG_H
# define SO_LONG_H

# include <MLX42/MLX42.h>
# include <libft.h>
# include <ft_printf/ft_printf.h>
# include <get_next_line/get_next_line.h>

# include <fcntl.h>
# include <stdio.h>

# define ELEMENTS "01PEC"

typedef struct s_point
{
    int     x;
    int     y;
}   t_point;

typedef struct s_image
{
    int image_w;
    int image_h;
    mlx_image_t *empty;
    mlx_image_t *wall;
    mlx_image_t *collect;
    mlx_image_t *exit1;
    mlx_image_t *exit2;
    mlx_image_t *start;
    mlx_image_t *player;
}   t_image;

typedef struct s_map
{
    mlx_t   *mlx;
    t_image     image;
    //map file
    //const char    *filename;
    char     **grid; //map
    int     rows; //y
    int     cols; //x
    //mlx size
    int     window_w;
    int     window_h;
    //scale
    int     scale;
    //player moves
    int     move;
    //collection numbers
    int     collect_all;
    int     collect_get;
    //player and exit numberss
    int     player_n;
    int     exit_n;
    //exit coord
    t_point     exit;
    //start coord
    t_point     start;
    //player curret location
    t_point     cur;
    //player next location
    t_point     next;
}   t_map;



void map_initialize(t_map *map, char *filename);
void    error_info(t_map *map, char *message);
void image_initialize(mlx_t *mlx, t_map *map);
void image_draw(mlx_t *mlx, t_map *map);
void my_keyhook(mlx_key_data_t keydata, void *param);
void player_move(t_map *map, t_image *image);
mlx_image_t *image_load(mlx_t *mlx, t_map *map, const char *path);
void    quit_game(t_map *map);
void    delete_map(t_map *map);
void    delete_image(t_map *map);
void    my_closehook(void *param);
int  check_elements(t_map *map);
int check_shape(t_map *map);
int check_wall(t_map *map);
int check_path(t_map *map);
void    delete_matrix(char **matrix, int i);
void    delete_image(t_map *map);
void my_resizehook(int32_t width, int32_t height, void *param);

#endif