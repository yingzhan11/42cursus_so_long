计划：

cheng the 'start' texture size

Bonus

**Make the player lose when they touch an enemy patrol.**

玩家struct， 敌人struct (位置，方向）

1-获取敌人数量，敌人起始位置，敌人方向（V & H）array

    2-检查敌人密度check denisty: (number of enemy) / (empty) < 10% ?

？？？3-path: V & H, two kind enemy. get enemy start place and end place， check valid path for game win

4-load enemy image

5-update enemy place, in s_mlx: double		delta_time;

typedef struct mlx
{
	void*		window;
	void*		context;
	int32_t		width;
	int32_t		height;
	double		delta_time;
}	mlx_t;

/**
 * Gets the elapsed time since MLX was initialized.
 * 
 * @return The amount of time elapsed in seconds.
 */
double mlx_get_time(void);

**Add some sprite animation.**

**Display the movement count directly on screen instead of writing it in the shell.**
