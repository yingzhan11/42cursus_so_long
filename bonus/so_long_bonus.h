/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:05:31 by yzhan             #+#    #+#             */
/*   Updated: 2024/07/04 09:44:50 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# define ELEMENTS "01PECHV"

typedef struct s_point
{
	int			x;
	int			y;
}	t_point;

typedef struct s_image
{
	int			image_w;
	int			image_h;
	mlx_image_t	*empty;
	mlx_image_t	*wall;
	mlx_image_t	*collect;
	mlx_image_t	*exit1;
	mlx_image_t	*exit2;
	mlx_image_t	*start;
	mlx_image_t	*player;
	mlx_image_t *enemy;
}	t_image;

typedef struct s_enemy
{
	char	type;
	char	dir; //dirction
	t_point	pos; //position
	t_point cur;
} t_enemy;

typedef struct s_map
{
	mlx_t		*mlx;
	t_image		image;
	char		**grid;
	int			rows;
	int			cols;
	int			window_w;
	int			window_h;
	int			scale;
	int			move;
	int			empty_n;
	int			collect_all;
	int			collect_get;
	int			exit_n;
	int			player_n;
	//enemy
	int			enemy_n;
	int			enemy_den; //density
	t_enemy		*enemy;
	//char		enemy_d;
	
	double		time;
	
	//t_point		enemy_sp;
	t_point		exit;
	t_point		start;
	t_point		cur;
	t_point		next;
}	t_map;

void	map_initialize(t_map *map, char *filename);
int		check_elements(t_map *map);
int		check_shape(t_map *map);
int		check_wall(t_map *map);
int		find_path(t_map *map, t_point cur, char **matrix);
int		check_path(t_map *map);
void	image_initialize(mlx_t *mlx, t_map *map);
void	image_draw(mlx_t *mlx, t_map *map);
void	my_keyhook(mlx_key_data_t keydata, void *param);
void	my_resizehook(int32_t width, int32_t height, void *param);
void	my_closehook(void *param);
void	player_move(t_map *map, t_image *image);
void	error_info(t_map *map, char *message);
void	quit_game(t_map *map);
void	delete_map(t_map *map);
void	delete_image(t_map *map);
void	delete_matrix(char **matrix, int i);

void my_updatehook(void *param);
void enemy_move(t_map *map, double time);
int check_enemy(t_map *map);

#endif
