#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include "MLX42/MLX42.h"
#include "libft.h"
#include "get_next_line/get_next_line.h"

#define WIDTH 1024
#define HEIGHT 512

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
		image->instances[0].y -= 32;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		image->instances[0].y += 32;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		image->instances[0].x -= 32;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		image->instances[0].x += 32;
}

int** read_map(const char* filename, int* rows, int* cols) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Failed to open map file\n");
        return NULL;
    }

    char *line;
    int** map = NULL;
    *rows = 0;
    *cols = 0;

    while ((line = get_next_line(fd)) != NULL) {
        if (*cols == 0) {
            *cols = ft_strlen(line) - 1; // exclude newline character
        }
        map = realloc(map, (*rows + 1) * sizeof(int*));
        map[*rows] = malloc(*cols * sizeof(int));
        for (int i = 0; i < *cols; i++) {
            map[*rows][i] = line[i] - '0';
        }
        (*rows)++;
        free(line);
    }

    close(fd);
    return map;
}

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
	int rows;
	int cols;
	int	**map = read_map("./map/map1.ber", &rows, &cols);

	//load map texture
	mlx_texture_t* wall_texture = mlx_load_png("./textures/Grass_Middle.png");
	mlx_texture_t* space_texture = mlx_load_png("./textures/FarmLand_Tile.png");
	
	//show map in window
	int y = 0;
	int x;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			mlx_image_t* img = NULL;
			if (map[y][x] == 1)
				img = mlx_texture_to_image(game.mlx, wall_texture);
			else
				img = mlx_texture_to_image(game.mlx, space_texture);
			if (img)
			{
				int tile_size = WIDTH/10;
				mlx_resize_image(img, tile_size, tile_size);
				mlx_image_to_window(game.mlx, img, x * tile_size, y * tile_size);
			}
			x++;
		}
		y++;
	}

	//load character
	mlx_texture_t* tex = mlx_load_png("./textures/Character_Hurt.png");

	int src_x = 0;        // X coordinate of the region in the texture
	int src_y = 0;        // Y coordinate of the region in the texture
	int region_width = 16;  // Width of the region
	int region_height = 16;
	game.image = mlx_new_image(game.mlx, region_width, region_height);
	copy_region_to_image(tex, game.image, src_x, src_y, region_width, region_height);
	//mlx_delete_texture(tex);
	mlx_resize_image(game.image, 16*4, 16*5);

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
