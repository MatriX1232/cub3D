/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:55:23 by msolinsk          #+#    #+#             */
/*   Updated: 2024/11/21 22:16:30 by msolinsk         ###   ########.fr       */
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
				*(unsigned int *)(dest_data + dest_pixel_index) = *(unsigned int *)(src_data + src_pixel_index);
			}
		}
	}
}
