#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MLX42/MLX42.h"
#include "libft.h"

#define WIDTH 1024
#define HEIGHT 512

//static mlx_image_t* image;

// -----------------------------------------------------------------------------

typedef struct game
{
	mlx_t* mlx;
	mlx_image_t* image;	
} game_t;

void copy_region_to_image(mlx_texture_t* texture, mlx_image_t* image, int src_x, int src_y, int width, int height) 
{
	int	x;
	int	y = 0;

	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			int texture_index = (src_y + y) * texture->width + (src_x + x);
			int image_index = y * width + x;
			((uint32_t*)image->pixels)[image_index] = ((uint32_t*)texture->pixels)[texture_index];
			x++;
		}
		y++;
	}
}

void ft_hook(void* param)
{
	game_t* game = param;	
	mlx_t* mlx = game->mlx;
	mlx_image_t *image = game->image;


	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		image->instances[0].x += 5;
}
/*
void	*ft_memset(void *b, int c, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
		((unsigned char *)b)[i++] = c;
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
*/
// -----------------------------------------------------------------------------

int32_t main(void)
{
	game_t game;

	//initailize window
	ft_bzero(&game, sizeof(game_t));
	if (!(game.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	//read map file

	//load map texture

	//show map in window

	mlx_texture_t* tex;
	tex = mlx_load_png("./textures/Character_Hurt.png");
/*
	if (!(image = mlx_texture_to_image(mlx, tex)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}*/

	int src_x = 0;        // X coordinate of the region in the texture
	int src_y = 0;        // Y coordinate of the region in the texture
	int region_width = 16;  // Width of the region
	int region_height = 16;
	game.image = mlx_new_image(game.mlx, region_width, region_height);
	copy_region_to_image(tex, game.image, src_x, src_y, region_width, region_height);
	//mlx_delete_texture(tex);
	mlx_resize_image(game.image, 64, 64);
	if (mlx_image_to_window(game.mlx, game.image, 0, 0) == -1)
	{
		mlx_close_window(game.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}	

	mlx_loop_hook(game.mlx, ft_hook, &game);

	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
