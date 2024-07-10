
#include "so_long_bonus.h"

//hook for keyboard input
void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = (t_map *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		quit_game(map, "Quit game.");
	if (ft_strchr(MOVEKEY, keydata.key) && keydata.action == MLX_PRESS && map->p_state == 0)
	{
		map->p_state = 1;
		if (keydata.key == MLX_KEY_W)
		{
			map->next = (t_point){map->cur.x, map->cur.y - 1};
			map->player.rows = 3;
		}
		if (keydata.key == MLX_KEY_S)
		{
			map->next = (t_point){map->cur.x, map->cur.y + 1};
			map->player.rows = 0;
		}
		if (keydata.key == MLX_KEY_A)
		{
			map->next = (t_point){map->cur.x - 1, map->cur.y};
			map->player.rows = 2;
		}
		if (keydata.key == MLX_KEY_D)
		{
			map->next = (t_point){map->cur.x + 1, map->cur.y};
			map->player.rows = 1;
		}
	}
	copy_anima_to_image(map->player.image, map->image.player_a, map->player.cols, map->player.rows);
}

//hook for resize the window
void	my_resizehook(int32_t width, int32_t height, void *param)
{
	t_map	*map;


	map = (t_map *)param;
	map->window_w = width;
	map->window_h = height;
	delete_image(map);

	image_initialize(map->mlx, map);
	image_draw(map->mlx, map);
}

//hook for close the window
void	my_closehook(void *param)
{
	t_map	*map;

	map = (t_map *)param;
	delete_map(map);
	exit(EXIT_SUCCESS);
}

//hook for close the window
void	my_updatehook(void *param)
{
	t_map *map;
	
	map = (t_map *)param;
	map->time = map->mlx->delta_time;
	enemy_update(map, map->time);
	player_update(map, map->time);
}