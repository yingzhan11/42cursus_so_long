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

//coordinate
typedef struct s_point
{
	int			x;
	int			y;
}	t_point;

/*
images
player_std, player_run, enemy_fly contain all frame of animation
*/
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

/*
enemy struct
img: the enemy image showed on window, is a frame in animation image
type: the path of enemy movement
	'H' type enemy moves in horizontal direction, 
	'V' type enemy moves in vertical direction
dir: current direction of enemy, including right&left (for H), up&down (for V)
pos: the position coordinate of enemy
col & row: record the frame of the enemy in its animation image
*/
typedef struct s_enemy
{
	mlx_image_t	*img;
	char		type;
	char		dir;
	t_point		pos;
	int			col;
	int			row;
}	t_enemy;

/*
player struct
image: a frame copy from player animation image
col & row: record the current frome info
*/
typedef struct s_player
{
	mlx_image_t	*image;
	int			col;
	int			row;
}	t_player;

/*
all params need for the game
grid: the copy of map file, rows is the lines number of maps
scale: the image size
move: the steps of player
p_state: the state of player, defaul is 0, means standing, 1 is for moving
time: the delta_time of mlx
info: the tip text print on window
cur: the player current position
next: the next position where player will move to
*/
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

//map init and check
void	map_initialize(t_map *map, char *filename);
int		check_elements(t_map *map);
int		check_shape(t_map *map);
int		check_wall(t_map *map);
void	get_player_position(t_map *map);
void	get_enemy_path(t_map *map);
int		check_path(t_map *map);
//image init and draw
void	image_initialize(mlx_t *mlx, t_map *map);
void	image_draw(mlx_t *mlx, t_map *map);
//my hook
void	my_keyhook(mlx_key_data_t keydata, void *param);
void	my_resizehook(int32_t width, int32_t height, void *param);
void	my_closehook(void *param);
void	my_updatehook(void *param);
//player and enemy move and animation updating func
void	player_update(t_map *map, double newtime);
void	player_move(t_map *map, mlx_image_t *image, int i);
void	enemy_update(t_map *map, double time);
void	enemy_move(t_map *map);
//tools
void	put_anima(mlx_image_t *img, mlx_image_t *anima, uint32_t c, uint32_t r);
void	delete_map(t_map *map);
void	delete_enemy(t_map *map);
void	delete_image(t_map *map);
void	delete_matrix(char **matrix, int i);
void	put_text_move(t_map *map);
void	put_text_info(t_map *map, char *info);
void	quit_game(t_map *map, char *message);
void	error_info(t_map *map, char *message);

#endif
