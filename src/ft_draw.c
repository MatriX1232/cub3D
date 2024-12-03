/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:55:23 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/03 13:56:25 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

void put_img_to_img(t_sprite *dest_img, t_sprite *src_img, int dest_x, int dest_y)
{
	int src_bpp, src_size_line, src_endian;
	int dest_bpp, dest_size_line, dest_endian;

	char *src_data = mlx_get_data_addr(src_img->img, &src_bpp, &src_size_line, &src_endian);
	char *dest_data = mlx_get_data_addr(dest_img->img, &dest_bpp, &dest_size_line, &dest_endian);

	int	src_width = src_img->width;
	int	src_height = src_img->height;

	for (int y = 0; y < src_height; y++)
	{
		for (int x = 0; x < src_width; x++)
		{
			int src_pixel_index = (y * src_size_line) + (x * (src_bpp / 8));
			int dest_pixel_index = ((dest_y + y) * dest_size_line) + ((dest_x + x) * (dest_bpp / 8));

			if (dest_pixel_index >= 0 && dest_pixel_index < dest_size_line * src_height)
			{
				ft_log("put_img_to_img: ", "dest_pixel_index is out of bounds", 2);
				*(unsigned int *)(dest_data + dest_pixel_index) = *(unsigned int *)(src_data + src_pixel_index);
			}
		}
	}
}

// void	put_img_to_img(t_sprite *dest_img, t_sprite *src_img, int dest_x, int dest_y)
// {
// 	int	x;
// 	int	y;

// 	for (y = 0; y < src_img->height; y++)
// 	{
// 		for (x = 0; x < src_img->width; x++)
// 		{
// 			int src_pixel = *(unsigned int *)(src_img->addr + (y * src_img->line_length) + (x * (src_img->bits_per_pixel / 8)));
// 			if (src_pixel != 0x00000000) // Assuming 0x00000000 is transparent
// 				*(unsigned int *)(dest_img->addr + ((dest_y + y) * dest_img->line_length) + ((dest_x + x) * (dest_img->bits_per_pixel / 8))) = src_pixel;
// 		}
// 	}
// }

void put_pixel_to_img(t_sprite *img, int x, int y, int color)
{
	if (img->addr && x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		int pixel_index = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
		*(unsigned int *)(img->addr + pixel_index) = color;
	}
}

void draw_sprite_to_buffer(t_cub3d *cub3d, t_sprite *sprite, int x_offset, int y_offset)
{
	int x, y;
	char *src_pixel;
	char *dst_pixel;
	int src_line_length = sprite->line_length;
	int dst_line_length = cub3d->buffer->line_length;
	int bytes_per_pixel = sprite->bits_per_pixel / 8;

	for (y = 0; y < sprite->height; y++)
	{
		if (y + y_offset < 0 || y + y_offset >= cub3d->win_height)
			continue;
		for (x = 0; x < sprite->width; x++)
		{
			if (x + x_offset < 0 || x + x_offset >= cub3d->win_width)
				continue;
			src_pixel = sprite->addr + y * src_line_length + x * bytes_per_pixel;
			dst_pixel = cub3d->buffer->addr + (y + y_offset) * dst_line_length + (x + x_offset) * bytes_per_pixel;
			unsigned int color = *(unsigned int *)src_pixel;
			if ((color & 0xFF000000) != 0xFF000000)
				*(unsigned int *)dst_pixel = color;
		}
	}
}

