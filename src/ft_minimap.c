/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 22:25:21 by msolinsk          #+#    #+#             */
/*   Updated: 2024/11/21 23:16:03 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

void	ft_draw_minimap(t_cub3d *cub3d)
{
	int		x;
	int		y;
	int		i;
	int		j;
	int		offset_x;

	offset_x = cub3d->win_width - (cub3d->map->width * 10);
	x = 0;
	while (x < cub3d->map->width)
	{
		y = 0;
		while (y < cub3d->map->height)
		{
			if (cub3d->map->grid[y][x] == '0')
			{
				i = 0;
				while (i < 10)
				{
					j = 0;
					while (j < 10)
					{
						put_pixel_to_img(cub3d->buffer, offset_x + x * 10 + i, y * 10 + j, 0x00FF00);
						j++;
					}
					i++;
				}
			}
			y++;
		}
		x++;
	}
}
