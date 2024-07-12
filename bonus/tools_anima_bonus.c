/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_anima_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:37:01 by yzhan             #+#    #+#             */
/*   Updated: 2024/07/11 16:50:05 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static uint32_t	get_pixel(mlx_image_t *image, uint32_t x, uint32_t y)
{
	uint8_t	*color;

	if (x >= image->width || y >= image->height)
		return (0xFF000000);
	color = image->pixels + (y * image->width + x) * sizeof(int32_t);
	return (get_rgba(*(color), *(color + 1), *(color + 2), *(color + 3)));
}

void	put_anima(mlx_image_t *img, mlx_image_t *anima, uint32_t c, uint32_t r)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	newpixel;
	uint32_t	width;
	uint32_t	height;

	height = 0;
	while (height < img->height)
	{
		width = 0;
		while (width < img->width)
		{
			x = c * img->width + width;
			y = r * img->height + height;
			newpixel = get_pixel(anima, x, y);
			mlx_put_pixel(img, width, height, newpixel);
			width++;
		}
		height++;
	}
}
