/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:26:28 by yzhan             #+#    #+#             */
/*   Updated: 2024/07/11 16:44:41 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>

# define ELEMENTS "01PECHV"
# define MOVEKEY "WASD"
# define PLAYER_SPEED 0.05
# define ENEMY_SPEED 1

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
	mlx_image_t	*player_std;
	mlx_image_t	*player_run;
	mlx_image_t	*enemy_fly;
	mlx_image_t	*text_title;
	mlx_image_t	*text_move;
	mlx_image_t	*text_info;
}	t_image;

typedef struct s_enemy
{
	mlx_image_t	*img;
	char		type;
	char		dir;
	t_point		pos;
	int			col;
	int			row;
}	t_enemy;

typedef struct s_player
{
	mlx_image_t	*image;
	int			col;
	int			row;
}	t_player;

typedef struct s_map
{
	mlx_t		*mlx;
	t_image		image;
	char		**grid;
	int			row;
	int			col;
	int			window_w;
	int			window_h;
	int			scale;
	int			move;
	int			collect_all;
	int			collect_get;
	int			exit_n;
	t_player	player;
	int			player_n;
	int			p_state;
	t_enemy		*enemy;
	int			enemy_n;
	double		time;
	char		*info;
	t_point		exit;
	t_point		start;
	t_point		cur;
	t_point		next;
}	t_map;

void	map_initialize(t_map *map, char *filename);
int		check_elements(t_map *map);
int		check_shape(t_map *map);
int		check_wall(t_map *map);
void	get_player_position(t_map *map);
void	get_enemy_path(t_map *map);
int		check_path(t_map *map);
void	image_initialize(mlx_t *mlx, t_map *map);
void	image_draw(mlx_t *mlx, t_map *map);
void	my_keyhook(mlx_key_data_t keydata, void *param);
void	my_resizehook(int32_t width, int32_t height, void *param);
void	my_closehook(void *param);
void	my_updatehook(void *param);
void	enemy_update(t_map *map, double time);
void	player_update(t_map *map, double newtime);
void	enemy_move(t_map *map);
void	player_move(t_map *map, mlx_image_t *image, int i);
void	put_anima(mlx_image_t *img, mlx_image_t *anima, uint32_t c, uint32_t r);
void	delete_map(t_map *map);
void	delete_enemy(t_map *map);
void	delete_image(t_map *map);
void	delete_matrix(char **matrix, int i);
void	error_info(t_map *map, char *message);
void	put_text_move(t_map *map);
void	put_text_info(t_map *map, char *info);
void	quit_game(t_map *map, char *message);

#endif
