# include "so_long.h"

static void param_check(int argc)
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

void window_initialize(t_map *map)
{
    int scale;
    int x;
    int y;

    x = map->cols / 16;
    y = map->rows / 16;
    if ( x >= y)
        scale = 160 / (x + 1);
    else
        scale = 160 / (y + 1);
    map->window_w = map->cols * scale;
    map->window_h = map->rows * scale;
    map->mlx = mlx_init(map->window_w, map->window_h, "so_long", true);
    if (!map->mlx)
		error_info(map, "Fail to initialize window");
}

int main(int argc, char **argv)
{
    t_map   map;

    ft_bzero(&map, sizeof(t_map));
    
    //0-check argc, argv
    param_check(argc);
    //1-check map file, and read map
    //map.filename = argv[1];
    map_initialize(&map, argv[1]);
    //2-initial window, based on map size  >>>TODO<<<
    window_initialize(&map);
    //2-initial images
    image_initialize(map.mlx, &map); 
	//3-draw image on window, map character, exit, colloction
    image_draw(map.mlx, &map);
    //4-hooks
    mlx_key_hook(map.mlx, my_keyhook, &map);
    mlx_resize_hook(map.mlx, my_resizehook, &map);
    mlx_close_hook(map.mlx, my_closehook, &map);
    //5-loop
    mlx_loop(map.mlx);
    //6-close
    mlx_terminate(map.mlx);
    return (EXIT_SUCCESS);
}