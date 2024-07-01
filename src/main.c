# include "so_long.h"

static void param_check(int argc, char **argv, t_map *map)
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
    else
        map->filename = argv[1];   
}

int main(int argc, char **argv)
{
    t_map   map;
    mlx_t *mlx;
    t_image image;

    map.image = &image;
    
    //0-check argc, argv
    param_check(argc, argv, &map);
    //1-check map file, and read map
    map_initialize(&map);
    //2-initial window, based on map size  >>>TODO<<<
    mlx = mlx_init(1024, 512, "MLX42", true);
    map.mlx = mlx;
    map.window_w = 1024;
    map.window_h = 512;
    if (!mlx)
		error_info(&map, "Fail to initialize window");
    //2-initial images
    image_initialize(mlx, &map, &image);
    
	//3-draw image on window, map character, exit, colloction
    image_draw(mlx, &map, &image);

    //hooks
    mlx_key_hook(mlx, my_keyhook, &map);
    // close hook
    mlx_close_hook(mlx, my_closehook, &map);
    
    //loop
    mlx_loop(mlx);
    
    //close
    mlx_terminate(mlx);
    return (EXIT_SUCCESS);
}