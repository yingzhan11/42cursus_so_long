#include "so_long_bonus.h"

static int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

static uint32_t get_pixel(mlx_image_t *image, uint32_t x, uint32_t y)
{
    uint8_t *color;

    if (x > image->width || y > image->height)
        return (0xFF000000);
    color = image->pixels + (y * image->width + x) * sizeof(int32_t);
    return (get_rgba(*(color), *(color + 1), *(color + 2), *(color + 3)));
}

void anima_to_image(mlx_image_t *image, mlx_image_t *anima, uint32_t cols, uint32_t rows)
{
	uint32_t x;
	uint32_t y;
    uint32_t newpixel;

	y = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			newpixel = get_pixel(anima, cols * image->width + x, rows * image->width + y);
			mlx_put_pixel(image, x, y, newpixel);
            x++;
		}
		y++;
	}
}
