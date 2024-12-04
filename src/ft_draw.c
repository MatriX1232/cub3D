/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:55:23 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/03 18:53:33 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

void	put_pixel_to_img(t_sprite *img, int x, int y, int color)
{
	int	pixel_index;

	if (img->addr && x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		pixel_index = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
		if ((color & 0xFF000000) != 0xFF000000)
			*(unsigned int *)(img->addr + pixel_index) = color;
	}
}

int	is_within_bounds(t_sprite *img, int x, int y)
{
	return (x >= 0 && x < img->width && y >= 0 && y < img->height);
}

void	blend_pixel(t_sprite *dest, t_sprite *src, int x, int y, int x_off, int y_off)
{
	unsigned int	src_color;
	unsigned int	dest_color;
	char			*src_p;
	char			*dest_p;

	src_p = src->addr + y * src->line_length + x * (src->bits_per_pixel / 8);
	dest_p = dest->addr + (y + y_off) * dest->line_length + (x + x_off) * (dest->bits_per_pixel / 8);
	src_color = *(unsigned int *)src_p;
	dest_color = *(unsigned int *)dest_p;
	if ((src_color & 0xFF000000) != 0xFF000000)
		*(unsigned int *)dest_p = src_color;
}

void	draw_2_buffer(t_sprite *dest, t_sprite *src, int x_offset, int y_offset)
{
	int	x;
	int	y;

	for (y = 0; y < src->height; y++)
	{
		for (x = 0; x < src->width; x++)
		{
			if (is_within_bounds(dest, x + x_offset, y + y_offset))
			{
				blend_pixel(dest, src, x, y, x_offset, y_offset);
			}
		}
	}
}
