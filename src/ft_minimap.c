/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 22:25:21 by msolinsk          #+#    #+#             */
/*   Updated: 2024/11/24 14:00:21 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

static void	ft_draw_scale(t_cub3d *cub3d, int x, int y, int color)
{
	int	i;
	int	j;
	int	offset_x;
	int	offset_y;

	offset_x = (cub3d->win_width - (cub3d->map->width * MINIMAP_SCALE)) - 10;
	offset_y = 10;
	i = 0;
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			put_pixel_to_img(cub3d->buffer, offset_x + (x * MINIMAP_SCALE) + i, offset_y + (y * MINIMAP_SCALE) + j, color);
			j++;
		}
		i++;
	}
}

void	ft_draw_minimap(t_cub3d *cub3d, int px, int py)
{
	int	x;
	int	y;

	if (cub3d->map->width <= 0 || cub3d->map->height <= 0)
		ft_log("Map width or height is <= 0", NULL, 2);
	x = 0;
	while (x < cub3d->map->width)
	{
		y = 0;
		while (y < cub3d->map->height)
		{
			if (cub3d->map->grid[y][x] == '0')
				ft_draw_scale(cub3d, x, y, MINIMAP_BG);
			else if (cub3d->map->grid[y][x] == '1')
				ft_draw_scale(cub3d, x, y, MINIMAP_FG);
			if (x == px && y == py)
				ft_draw_scale(cub3d, x, y, 0xFF0000);
			y++;
		}
		x++;
	}
}
