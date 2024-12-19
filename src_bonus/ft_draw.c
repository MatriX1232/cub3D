/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:55:23 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/04 15:35:46 by msolinsk         ###   ########.fr       */
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

void	blend_pixel(t_sprite *dest, t_sprite *src, t_vec2 v, t_vec2 off)
{
	unsigned int	src_color;
	char			*src_p;
	char			*dest_p;

	src_p = src->addr + v.y * src->line_length + \
		v.x * (src->bits_per_pixel / 8);
	dest_p = dest->addr + (v.y + off.y) * dest->line_length + \
		(v.x + off.x) * (dest->bits_per_pixel / 8);
	src_color = *(unsigned int *)src_p;
	if ((src_color & 0xFF000000) != 0xFF000000)
		*(unsigned int *)dest_p = src_color;
}

void	draw_2_buffer(t_sprite *dest, t_sprite *src, int x_offset, int y_offset)
{
	int	x;
	int	y;

	y = 0;
	while (y < src->height)
	{
		x = 0;
		while (x < src->width)
		{
			if (is_within_bounds(dest, x + x_offset, y + y_offset))
				blend_pixel(dest, src, \
					(t_vec2){x, y}, \
					(t_vec2){x_offset, y_offset});
			x++;
		}
		y++;
	}
}
